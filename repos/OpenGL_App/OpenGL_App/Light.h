#pragma once

// Zaladowanie naglowka z GLEW.
#include <GL\glew.h>

// Zaladowanie naglowka z GLM.
#include <glm\glm.hpp>

#include <glm\gtc\matrix_transform.hpp>

// Zaladowanie naglowka z mapa cieniowania.
#include "ShadowMap.h"

class Light
{
public:
	/// Konstruktor.
	Light();

	/// Konstrutkor.
	Light(GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,  GLfloat dIntensity);

	/// Zwroc mape cieniowania.
	ShadowMap* GetShadowMap()
	{
		return shadowMap;
	}

	/// Destruktor.
	~Light();

protected:
	glm::vec3 colour; // Kolor.
	GLfloat ambientIntensity; // Intensywnosc swiatla otoczenia.
	GLfloat diffuseIntensity; // Stopieñ rozproszenia swiatla.

	glm::mat4 lightProj; // Jak swiatlo widzi.

	ShadowMap* shadowMap; // Mapa cieniowania.
};

