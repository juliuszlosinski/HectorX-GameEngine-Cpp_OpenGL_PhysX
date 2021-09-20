#include "Light.h"

/// Konstruktor.
Light::Light()
{
	// 1. Ustawienie koloru ~ jak duzo koloru kazdego piksela ma byc pokazane.
	colour = glm::vec3(1.0f, 1.0f, 1.0f);

	// 2. Ustawienie intesywnosci oswietlenia otoczenia.
	ambientIntensity = 1.0f;

	// 3. Ustawienie stopnia rozproszenia swiatla.
	diffuseIntensity = 0.0f;
}

/// Konstruktor.
Light::Light(GLfloat shadowWidth, GLfloat shadowHeight,
	GLfloat red, GLfloat green, GLfloat blue, 
			 GLfloat aIntensity, GLfloat dIntensity)
{
	// 0. Utworzenie mapy cieniowania.
	shadowMap = new ShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);

	// 1. Ustawienie koloru ~ jak duzo koloru kazdego piksela ma byc pokazane.
	colour = glm::vec3(red, green, blue);

	// 2. Ustawienie intesywnosci oswietlenia otoczenia.
	ambientIntensity = aIntensity;

	// 3. Ustawienie stopnia rozproszenia swiatla.
	diffuseIntensity = dIntensity;
}

/// Destruktor.
Light::~Light()
{

}
