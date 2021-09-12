#include "Light.h"

/// Konstruktor.
Light::Light()
{
	// 1. Ustawienie koloru ~ jak duzo koloru kazdego piksela ma byc pokazane.
	colour = glm::vec3(1.0f, 1.0f, 1.0f);

	// 2. Ustawienie intesywnosci oswietlenia otoczenia.
	ambientIntensity = 1.0f;

	// 3. Kierunek padania œwiat³a.
	direction = glm::vec3(0.0f, -1.0f, 0.0f);

	// 4. Ustawienie stopnia rozproszenia swiatla.
	diffuseIntensity = 0.0f;
}

/// Konstruktor.
Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
{
	// 1. Ustawienie koloru ~ jak duzo koloru kazdego piksela ma byc pokazane.
	colour = glm::vec3(red, green, blue);

	// 2. Ustawienie intesywnosci oswietlenia otoczenia.
	ambientIntensity = aIntensity;

	// 3. Ustawienie kierunku padania œwiat³a.
	direction = glm::vec3(xDir, yDir, zDir);

	// 4. Ustawienie stopnia rozproszenia swiatla.
	diffuseIntensity = dIntensity;
}

/// Uzywanie swiatla.
void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
	// 1. Ustawienie uniformu dla koloru.
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);

	// 2. Ustawienie uniformu dla intesywnosci swiatla otoczenia.
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	// 3. Ustawienie uniformu dla kierunku.
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);

	// 4. Ustawienie uniformu dla intensywnosci swiatla rozproszenia.
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

/// Destruktor.
Light::~Light()
{

}