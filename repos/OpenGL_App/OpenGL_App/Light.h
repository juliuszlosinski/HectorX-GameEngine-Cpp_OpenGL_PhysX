#pragma once

// Zaladowanie naglowka z GLEW.
#include <GL\glew.h>

// Zaladowanie naglowka z GLM.
#include <glm\glm.hpp>


class Light
{
public:
	/// Konstruktor.
	Light();

	/// Konstrutkor.
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);

	/// Uzywanie swiatla.
	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	~Light();

private:
	glm::vec3 colour; // Kolor.
	GLfloat ambientIntensity; // Intensywnosc swiatla otoczenia.

	glm::vec3 direction; // Kierunek padania swiatla.
	GLfloat diffuseIntensity; // Stopieñ rozproszenia swiatla.
};

