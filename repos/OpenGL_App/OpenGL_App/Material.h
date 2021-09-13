#pragma once

#include <GL\glew.h>

class Material
{
public:

	/// Konstrutkor.
	Material();

	/// Konstruktor.
	Material(GLfloat sIntensity, GLfloat shine);

	/// Uzycie materialu.
	void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

	/// Destruktor.
	~Material();

private:
	GLfloat specularIntensity; // Jak mocno naswietlone.
	GLfloat shininess; // Jak bardzo skupione odbicie swiatla. Im wieksze tym bardziej skupione (metal) a im mniejsze tym mniej skupione (drewno).
};

