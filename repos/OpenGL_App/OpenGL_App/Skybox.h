#pragma once

// Za³¹czenie nag³ówka z wektorem.
#include <vector>

// Za³¹czenie nag³ówka z operacjami na ³añcuchach znaków.
#include <string>

// Za³¹czenie nag³ówka z nowoczesn¹ wersj¹ OpenGL.
#include <GL\glew.h>

// Za³¹czenie nag³ówka z powszechnie u¿ywanymi wartoœciami.
#include "CommonValues.h"

// Za³¹czenie nag³ówka z macierzami.
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// Za³¹czenie nag³ówka z siatk¹.
#include "Mesh.h"

// Za³¹czenie nag³ówka z shaderem.
#include "Shader.h"

class Skybox
{
public:
	/// Konstruktor.
	Skybox();

	/// Konstrutkor.
	Skybox(std::vector<std::string> faceLocations);

	/// Rysowanie.
	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	/// Destruktor.
	~Skybox();
private:
	Mesh* skyMesh; // Siatka skybox'a.
	Shader* skyShader; // Shader do shadera.

	GLuint textureId; // Identyfikator tekstury.
	GLuint uniformProjection; // Identyfikator uniformu projekcji.
	GLuint uniformView; // Identyfikator uniformu widoku.
};

