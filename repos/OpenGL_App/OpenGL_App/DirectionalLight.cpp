#include "DirectionalLight.h"

/// Konstruktor.
DirectionalLight::DirectionalLight():Light()
{
	// 1. Kierunek padania œwiat³a.
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

/// Konstruktor.
DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
								   GLfloat aIntensity, GLfloat dIntensity,
								   GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(red, green, blue, aIntensity, dIntensity)
{
	// 1. Ustawienie kierunku padania œwiat³a.
	direction = glm::vec3(xDir, yDir, zDir);
}

/// Uzywanie swiatla.
void DirectionalLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation)
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
DirectionalLight::~DirectionalLight()
{

}