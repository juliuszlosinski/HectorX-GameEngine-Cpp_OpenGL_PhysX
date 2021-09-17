#include "SpotLight.h"

/// Konstruktor.
SpotLight::SpotLight() : PointLight()
{
	// 1. Ustawienie kierunku.
	direction = glm::vec3(0.0f, -1.0f, 0.0f);

	// 2. Ustawienie kata.
	edge = 0.0f;

	// 3. Ustawienie wartosci sprocesowanego kata.
	procEdge = cos(glm::radians(edge));
}

/// Konstruktor.
SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, 
					 GLfloat aIntensity, GLfloat dIntensity, 
					 GLfloat xPos, GLfloat yPos, GLfloat zPos, 
					 GLfloat xDir, GLfloat yDir, GLfloat zDir, 
					 GLfloat con, GLfloat lin, GLfloat exp, 
					 GLfloat edg) : PointLight(red, green, blue, aIntensity, dIntensity, xPos, yPos, zPos, con, lin, exp)
{
	// 1. Ustawienie kierunku.
	direction = glm::normalize(glm::vec3(xDir, yDir, zDir));

	// 2. Ustawienie kata.
	edge = edg;

	// 3. Ustawienie wartosci sprocesowanego kata.
	procEdge = cos(glm::radians(edge));
}

/// Uzywanie swiatla.
void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, 
						 GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation, 
						 GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
						 GLuint edgeLocation)
{
	// 1. Ustawienie uniformu dla koloru.
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);

	// 2. Ustawienie uniformu dla intesywnosci swiatla otoczenia.
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	// 3. Ustawienie uniformu dla intensywnosci swiatla rozproszenia.
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

	// 4. Ustawienie uniformu dla pozycji zrodla swiatla.
	glUniform3f(positionLocation, position.x, position.y, position.z);

	// 5. Ustawienie uniformu dla stalej ~ c.
	glUniform1f(constantLocation, constant);

	// 6. Ustawienie uniformu dla liniowej ~ bx.
	glUniform1f(linearLocation, linear);

	// 7. Ustawienie uniformu dla eksponenty ~ ax^2.
	glUniform1f(exponentLocation, exponent);

	// 8. Ustawienie uniformu dla kierunku.
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);

	// 9. Ustawienie uniformu dla kata.
	glUniform1f(edgeLocation, procEdge);
}

/// Ustawienie pozycji swiatla oraz kierunku do którego jest skierowany (front).
void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	// 1. Ustawienie pozycji zrodla swiatla.
	position = pos;

	// 2. Ustawienie kierunku do, którego jest skierowane zrodlo swiatlo (front).
	direction = dir;
}

/// Destuktor.
SpotLight::~SpotLight()
{

}