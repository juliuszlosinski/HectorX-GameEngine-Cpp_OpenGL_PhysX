#pragma once

// Zaladowanie GLEW.
#include <GL\glew.h>

// Zaladowanie pliku do ladowania tekstur/ obrazkow.
#include "stb_image.h"

class Texture
{
public:
	/// Konstruktor.
	Texture();

	/// Konstrutkor.
	Texture(char* fileLoc);

	/// £adowanie tekstury.
	void LoadTexture();

	/// U¿ywanie tekstury.
	void UseTexture();

	/// Usuniêcie tekstury.
	void ClearTexture();

	/// Destruktor.
	~Texture();
private:
	GLuint textureID;
	int width; // Dlugosc tekstury.
	int height; // Wysokosc tekstury.
	int bitDepth; // Glebia.

	char* fileLocation; // Lokalizacja pliku z tekstura.
};

