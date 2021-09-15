#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	/// Konstruktor.
	DirectionalLight();

	/// Konstrutkor.
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
					 GLfloat aIntensity, GLfloat dIntensity, 
					 GLfloat xDir, GLfloat yDir, GLfloat zDir);

	/// Uzywanie swiatla.
	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	/// Destruktor.
	~DirectionalLight();

private:
	glm::vec3 direction; // Kierunek padania swiatla.
};

