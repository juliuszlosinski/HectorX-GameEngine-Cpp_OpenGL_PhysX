#include "Light.h"

/// Konstruktor.
Light::Light()
{
	// 1. Ustawienie koloru ~ jak duzo koloru kazdego piksela ma byc pokazane.
	colour = glm::vec3(1.0f, 1.0f, 1.0f);

	// 2. Ustawienie intesywnosci oswietlenia otoczenia.
	ambientIntensity = 1.0f;
}

/// Konstruktor.
Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity)
{
	// 1. Ustawienie koloru ~ jak duzo koloru kazdego piksela ma byc pokazane.
	colour = glm::vec3(red, green, blue);

	// 2. Ustawienie intesywnosci oswietlenia otoczenia.
	ambientIntensity = aIntensity;
}

/// Uzywanie swiatla.
void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation)
{
	// 1. Ustawienie uniformu dla koloru.
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);

	// 2. Ustawienie uniformu dla intesywnosci swiatla otoczenia.
	glUniform1f(ambientIntensityLocation, ambientIntensity);
}

/// Destruktor.
Light::~Light()
{

}