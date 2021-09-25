#include "Skybox.h"

/// Konstruktor.
Skybox::Skybox()
{

}

/// Konstrutkor.
Skybox::Skybox(std::vector<std::string> faceLocations)
{
	// -----USTAWIANIE SHADERA----:

	// 1. Utworzenie shadera.
	skyShader = new Shader();

	// 2. Utworzenie z plikow.
	skyShader->CreateFromFiles("Shaders/skybox.vert", "Shaders/skybox.frag");

	// 3. Uzyskanie lokalizacji uniformu projekcji.
	uniformProjection = skyShader->GetProjectionLocation();

	// 4. Uzyskanie lokalizacji uniformu widoku.
	uniformView = skyShader->GetViewLocation();

	// -----USTAWIANIE TEKSTURY-----:

	// 1. Wygenerowanie tekstury.
	glGenTextures(1, &textureId);

	// 2. Ustawienie tekstury jako roboczej.
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	// 3. Ladowanie obrazka oraz zapisywanie jego parametrow.
	int width;   // Dlugosc obrazka.
	int height;   // Wysokosc obrazka.
	int bitDepth; // Glebia obrazka.

	for (size_t i = 0; i < 6; i++)
	{
		unsigned char* texData = stbi_load(faceLocations[i].c_str(), &width, &height, &bitDepth, 0);
		if (!texData)
		{
			printf("Failed to find: %s\n", faceLocations[i].c_str());
			return;
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		stbi_image_free(texData);
	}

	// 4. Owijanie tekstury (jest ustawiane powtarzanie).
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// 5. Ustawianie filtrow (jak ma sie zachowywac tekstura w kontekscie odleglosci).
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// ----USTAWIENIE SIATKI----

	// 1. Utworzenie indeksow.
	unsigned int skyboxIndices[] = {
		// FRONT
		0, 1, 2,
		2, 1, 3,
		// RIGHT
		2, 3, 5,
		5, 3, 7,
		// BACK
		5, 7, 4,
		4, 7, 6,
		// LEFT
		4, 6, 0,
		0, 6, 1,
		// TOP
		4, 0, 5,
		5, 0, 2,
		// BOTTOM
		1, 6, 3,
		3, 6, 7
	};

	// 2. Utworzenie wierzcholkow.
	float skyboxVertices[] = {
		-1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f, // 0
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f, // 1
		1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f, // 2
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f, // 3

		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f, // 4
		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f, // 5
		-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f, // 6
		1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f  // 7
	};

	// 3. Utworzenie siatki.
	skyMesh = new Mesh();
	skyMesh->CreateMesh(skyboxVertices, skyboxIndices, 64, 36);
}

/// Rysowanie.
void Skybox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	// 0. Usuniecie 4 kolumny z translacja.
	viewMatrix = glm::mat4(glm::mat3(viewMatrix));

	// 1. Wylaczenie maski glebi.
	glDepthMask(GL_FALSE);

	// 2. Ustawienie shadera.
	skyShader->UseShader();
	
	// 3. Przeslanie macierzy projekcji do wskazanego uniform'u.
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	// 4. Przeslanie macierzy widoku do wskazanego uniform'u.
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// 5. Aktywowanie jednostki tekstury.
	glActiveTexture(GL_TEXTURE0);

	// 6. Polaczenie tekstury z aktywowana jednostka tekstury.
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	// 7. Walidacja programu,czy wszystkie wartosc dobrze zostaly polaczone ze shaderem itp..
	skyShader->Validate();

	// 8. Renderowanie siatki.
	skyMesh->RenderMesh();

	// 9. Wlaczenie maski glebi.
	glDepthMask(GL_TRUE);
}

/// Destruktor.
Skybox::~Skybox()
{

}