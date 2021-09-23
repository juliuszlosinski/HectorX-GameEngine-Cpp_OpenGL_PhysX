#define STB_IMAGE_IMPLEMENTATION

#include <assimp/Importer.hpp>

#include <stdio.h>

// Za³¹czenie pliku nag³ówkowego z wektorem.
#include <vector>

// Za³¹czenie pliku nag³ówkowego z matematyk¹.
#include <cmath>

// Za³¹czenie pliku nag³ówkowego z ³añcuchami znaków.
#include <string.h>

// Za³¹czenie pliku nag³ówkowego z GLEW.
#include <GL/glew.h>

/// Za³¹czenie pliku nag³ówkowego z GLFW.
#include <GLFW/glfw3.h>

// Za³¹czenie GLM.
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "CommonValues.h"

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "Model.h"

GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
uniformSpecularIntensity = 0, uniformShininess = 0, uniformOmniLightPos = 0, uniformFarPlane = 0;

Model xwing;
Model blackhawk;


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
Camera camera;
Shader directionalShadowShader;
Shader omniShadowShader;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;

Material shinyMaterial;
Material dullMaterial;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
GLfloat blackHawkAngle = 0.0f;

unsigned int pointLightCount = 0, spotLightCount = 0;

// Deklaracja zmiennych.
const float toRadians = 3.14159265f / 180.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

/// Obliczanie normalnych wektorow.
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount, unsigned int vLength, unsigned normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		// 1. Mnozymy przez vLength zeby uzyskac dostep do pierwszej wartosci wierzcholka.
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;

		// 2. Zdefiniowanie krawedzi (polaczenie dwoch pozycji zeby stworzyc linie).
		// 2.1 Stworzenie takich dwoch krawedzi.
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);

		// 2.2 Uzycie cross product na tych dwoch liniach zeby uzyskac normal.
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		// 3. Dodanie offsetu zeby przejsc do normalnego.
		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;

		// 4. Dodawanie normali.
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		// 5. Usrednianie.
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects()
{
	/// 0.Tworzenie indeksów dla IBO.
	unsigned int indices[] = {
		0, 3, 1, // Jedna strona piramidy.
		1, 3, 2, // Drugo strona piramidy.
		2, 3, 0, // Frontalna strona piramidy.
		0, 1, 2  // Podstawa piramidy.
	};

	// 1. Utworzenie wierzcho³ków trójk¹ta.
	GLfloat vertices[] = {
		//   x      y      z		  u	   v		 nx    ny    nz
			-1.0f, -1.0f, -0.6f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,			0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,		0.0f, -1.0f, 0.0f
	};

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	// 2. Utworzenie siatki.
	Mesh* obj1 = new Mesh();

	// 3. Utworzenie siatki.
	obj1->CreateMesh(vertices, indices, 32, 12);

	// 4. Dodanie do listy.
	meshList.push_back(obj1);

	// 2. Utworzenie siatki.
	Mesh* obj2 = new Mesh();

	// 3. Utworzenie siatki.
	obj2->CreateMesh(vertices, indices, 32, 12);

	// 4. Dodanie do listy.
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 4 * 8, 6);
	meshList.push_back(obj3);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	directionalShadowShader = Shader();
	directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");

	omniShadowShader = Shader();
	omniShadowShader.CreateFromFiles("Shaders/omni_shadow_map.vert", "Shaders/omni_shadow_map.geom", "Shaders/omni_shadow_map.frag");
}

void RenderScene()
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brickTexture.UseTexture();
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	meshList[0]->RenderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	dirtTexture.UseTexture();
	dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	meshList[1]->RenderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	plainTexture.UseTexture();
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	meshList[2]->RenderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 10.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	xwing.RenderModel();

	blackHawkAngle += 0.1f;
	if (blackHawkAngle > 360)
	{
		blackHawkAngle = 0.0f;
	}

	model = glm::mat4(1.0f);
	model = glm::rotate(model, -blackHawkAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-8.0f, 2.0f, 0.0f));
	model = glm::rotate(model, -20.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, -90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	blackhawk.RenderModel();
}

void DirectionalShadowMapPass(DirectionalLight* light)
{
	// 1. Uzycie shadera.
	directionalShadowShader.UseShader();

	// 2. Ustawienie parametrow portu widoku.
	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

	// 3. Zapisanie.
	light->GetShadowMap()->Write();

	// 4. Czyszczenie bufora.
	glClear(GL_DEPTH_BUFFER_BIT);

	// 5. Zdobycie pozycji.
	uniformModel = directionalShadowShader.GetModelLocation();

	// 6. Przeslanie widoku oraz projekcji z punktu widzenia kierunukowego swiatla.
	glm::mat4 res = light->CalculateLightTransform();
	directionalShadowShader.SetDirectionalLightTransform(&res);

	// 7. Renderowanie sceny.
	RenderScene();

	// 8. Zdjecie bufora.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OmniShadowMapPass(PointLight* light)
{
	// 1. Uzycie shadera.
	omniShadowShader.UseShader();

	// 2. Ustawienie parametrow portu widoku.
	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

	// 3. Zapisanie.
	light->GetShadowMap()->Write();

	// 4. Czyszczenie bufora.
	glClear(GL_DEPTH_BUFFER_BIT);

	// 5. Zdobycie pozycji.
	uniformModel = omniShadowShader.GetModelLocation();

	// 6. Uzyskanie lokalizacji polozenia swiatla.
	uniformOmniLightPos = omniShadowShader.GetOmniLightPosLocation();

	// 7. Uzyskanie lokalizajci odleglosci na jaka moze patrzec kamera.
	uniformFarPlane = omniShadowShader.GetFarPlaneLocation();

	// 8. Przeslanie polozenia kamery do shadera.
	glUniform3f(uniformOmniLightPos, light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);

	// 9. Przeslanie odleglosci na jaka moze patrzec kamera do shadera.
	glUniform1f(uniformFarPlane, light->GetFarPlane());

	// 10. Przeslanie macierzy transformacji (6 stron: lewa, prawa, gora, dol, przod, tyl) ~ pozniej w shaderze uzyskamy pozycje fragmentu relatywnie do punktu widzenia (relative to praticular view).
	std::vector<glm::mat4> lightTransform = light->CalculateLightTransform();
	omniShadowShader.SetLightMatrices(lightTransform);

	// 11. Renderowanie sceny.
	RenderScene();

	// 12. Zdjecie bufora oraz ustywienie domyslnego czyli finalnej sceny.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderPass(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	// 1. Uzywanie shadera.
	shaderList[0].UseShader();

	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectionLocation();
	uniformView = shaderList[0].GetViewLocation();
	uniformEyePosition = shaderList[0].GetEyePosition();
	uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
	uniformShininess = shaderList[0].GetShininessLocation();

	glViewport(0, 0, 1366, 768);

	// 9.2 Czyszczenie okna (bufora z kolorami oraz bufora z g³êbi¹).
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

	shaderList[0].SetDirectionalLight(&mainLight);
	shaderList[0].SetPointLights(pointLights, pointLightCount);
	shaderList[0].SetSpotLights(spotLights, spotLightCount);
	glm::mat4 trans = mainLight.CalculateLightTransform();
	shaderList[0].SetDirectionalLightTransform(&trans);

	mainLight.GetShadowMap()->Read(GL_TEXTURE1);
	shaderList[0].SetTexture(0);
	shaderList[0].SetDirectionalShadowMap(1);

	glm::vec3 lowerLight = camera.getCameraPosition();
	lowerLight.y -= 0.3f;
	spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

	RenderScene();
}

int main(void)
{
	mainWindow = Window(1366, 768);
	//mainWindow = Window(800, 600);
	mainWindow.Initialise();

	/// * Utworzenie trojk¹ta.
	CreateObjects();

	/// * Kompilacja shaderow ~ utworzenie programu.
	CreateShaders();

	/// * Inicjalizacja kamery.
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	brickTexture = Texture((char*)("Textures/machine.png"));
	brickTexture.LoadTextureA();

	dirtTexture = Texture((char*)("Textures/window.png"));
	dirtTexture.LoadTextureA();

	plainTexture = Texture((char*)("Textures/dirt.png"));
	plainTexture.LoadTextureA();

	shinyMaterial = Material(4.0f, 256);
	dullMaterial = Material(0.3f, 4);

	xwing = Model();
	xwing.LoadModel("Models/x-wing.obj");

	blackhawk = Model();
	blackhawk.LoadModel("Models/uh60.obj");

	mainLight = DirectionalLight(2048, 2048,
		1.0f, 1.0f, 1.0f,
		0.1f, 0.3f,
		0.0f, -15.0f, -10.0f);


	pointLights[0] = PointLight(1024, 1024,
								0.01f, 100.0f,
								0.0f, 0.0f, 1.0f,
								0.0f, 0.1f,
								0.0f, 0.0f, 0.0f,
								0.3f, 0.2f, 0.1f);
	pointLightCount++;
	pointLights[1] = PointLight(
								1024, 1024,
								0.01f, 100.0f, 
								0.0f, 1.0f, 0.0f,
								0.0f, 0.1f,
								-4.0f, 2.0f, 0.0f,
								0.3f, 0.1f, 0.1f);
	pointLightCount++;

	spotLights[0] = SpotLight(
								1024, 1024,
								0.01f, 100.0f,
								1.0f, 1.0f, 1.0f,
								0.0f, 2.0f,
								0.0f, 0.0f, 0.0f,
								0.0f, -1.0f, 0.0f,
								1.0f, 0.0f, 0.0f,
								20.0f);
	spotLightCount++;
	spotLights[1] = SpotLight(
								1024, 1024,
								0.01f, 100.0f,
								1.0f, 1.0f, 1.0f,
								0.0f, 1.0f,
								0.0f, -1.5f, 0.0f,
								-100.0f, -1.0f, 0.0f,
								1.0f, 0.0f, 0.0f,
								20.0f);
	spotLightCount++;


	/// * Ustawianie projekcji kamery (sposobu widzenia).
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);
	// kat widzenia,		wspó³czynnik proporcji,		z k¹d widzimy,  do k¹d

	// 9. Pêtla dzia³ania okna.
	while (!mainWindow.getShouldClose())
	{
		// 9.0 Uzyskanie czasu.
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime;  // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;

		// 9.1 Zdab¹dz oraz obs³uz zdarzenia wykonywane przez u¿ytkownika. (User Input Events)
		glfwPollEvents();

		camera.keyControl(mainWindow.getKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Ustawienie wszystkich map cieniowania, do których zosta³y zapisane wyniki.
		DirectionalShadowMapPass(&mainLight);
		for (size_t i = 0; i < pointLightCount; i++)
		{
			OmniShadowMapPass(&pointLights[i]);
		}
		for (size_t i = 0; i < spotLightCount; i++)
		{
			OmniShadowMapPass(&spotLights[i]);
		}
		RenderPass(projection, camera.calculateViewMatrix());

		/// 7. Zwolnienie programu.
		glUseProgram(0);

		/// ------------------------------

		// 9.3 Zamiana buforów (oryginalny na ten, na który widzi u¿ytkownik).
		mainWindow.SwapBuffers();
	}

	return 0;
}