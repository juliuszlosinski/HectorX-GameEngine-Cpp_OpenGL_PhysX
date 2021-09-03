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
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity);

	/// Uzywanie swiatla.
	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation);

	~Light();

private:
	glm::vec3 colour; // Kolor.
	GLfloat ambientIntensity; // Intensywnosc swiatla otoczenia.
};

