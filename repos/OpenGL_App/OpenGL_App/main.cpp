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
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

// Za³¹czenie GLM.
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
Camera camera;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Deklaracja zmiennych.
const float toRadians = 3.14159265f / 180.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

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
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	// 2. Utworzenie siatki.
	Mesh* obj1 = new Mesh();

	// 3. Utworzenie siatki.
	obj1->CreateMesh(vertices, indices, 12, 12);

	// 4. Dodanie do listy.
	meshList.push_back(obj1);

	// 2. Utworzenie siatki.
	Mesh* obj2 = new Mesh();

	// 3. Utworzenie siatki.
	obj2->CreateMesh(vertices, indices, 12, 12);

	// 4. Dodanie do listy.
	meshList.push_back(obj2);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main(void)
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();

	/// * Utworzenie trojk¹ta.
	CreateObjects();

	/// * Kompilacja shaderow ~ utworzenie programu.
	CreateShaders();

	/// * Inicjalizacja kamery.
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;

	/// * Ustawianie projekcji kamery (sposobu widzenia).
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);
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

		// 9.2 Czyszczenie okna (bufora z kolorami oraz bufora z g³êbi¹).
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/// ---------- Rysowanie ---------
		/// 1. Wybranie u¿ywanego programu (Shader programu) czyli kaze znalezc karcie graficznej, zeby znalazla program o tym identyfikatorze oraz zeby go u¿y³a.
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		meshList[1]->RenderMesh();

		/// 7. Zwolnienie programu.
		glUseProgram(0);

		/// ------------------------------

		// 9.3 Zamiana buforów (oryginalny na ten, na który widzi u¿ytkownik).
		mainWindow.SwapBuffers();
	}

	return 0;
}