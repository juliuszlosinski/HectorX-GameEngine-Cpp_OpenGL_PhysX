#pragma once
#include "PointLight.h"
class SpotLight : public PointLight
{
public:
	/// Konstruktor.
	SpotLight();

	/// Konstruktor.
	SpotLight(GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat near, GLfloat far,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat xDir, GLfloat yDir, GLfloat zDir,
		GLfloat con, GLfloat lin, GLfloat exp,
		GLfloat edg);

	/// Uzywanie swiatla.
	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
				  GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation,
				  GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
				  GLuint edgeLocation);

	/// Ustawienie swiatla.
	void SetFlash(glm::vec3 pos, glm::vec3 dir);

	// Prze³¹czenie œwiat³a.
	void Toggle() { isOn = !isOn; }
	
	/// Destruktor.
	~SpotLight();

private:
	glm::vec3 direction; // Kierunek swiecenia.
	
	GLfloat edge; // Kat.
	GLfloat procEdge; // Sprocesowany kat.

	bool isOn;
};

