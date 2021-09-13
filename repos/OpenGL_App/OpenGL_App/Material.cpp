#include "Material.h"

/// Konstruktor.
Material::Material()
{
	// 1. Ustawienie wartosci poczatkowych.
	specularIntensity = 0.0f;
	shininess = 0.0f;
}

/// Konstuktor.
Material::Material(GLfloat sIntensity, GLfloat shine)
{
	// 1. Ustawienie wartosci poczatkowych.
	// 1.1 Mocy oswietlenia.
	specularIntensity = sIntensity;

	// 1.2 Wspolczynnika skupienia swiatla.
	shininess = shine;
}

/// Uzyj materialu czyli wloz wartosci do miejsc, do ktorych uzyslismy lokalizacje (lokalizacja uniformow).
void Material:: UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
{
	// 1. Wlozenie wartosci mocy oswietlenia do wskazanej lokalizacji.
	glUniform1f(specularIntensityLocation, specularIntensity);

	// 2. Wlozenie wartosci wspolczynnika skupienia swiatla ~ shininess do wskazanej lokalizacji.
	glUniform1f(shininessLocation, shininess);

}

/// Destruktor.
Material::~Material()
{

}