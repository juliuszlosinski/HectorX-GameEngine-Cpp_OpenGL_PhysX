#pragma once

/// Za³¹czenie nag³ówka do wypisywania.
#include <stdio.h>

/// Za³¹czenia nag³ówka do u¿ywania OpenGL oraz rozszerzeñ.
#include <GL\glew.h>

class ShadowMap
{
public:
	/// Konstruktor.
	ShadowMap();

	/// Inicjalizacja (inicjalizacja parametrów tekstury).
	virtual bool Init(GLuint width, GLuint height);

	/// Zapisywanie.
	virtual void Write();

	/// Wczytywanie.
	virtual void Read(GLenum textureUnit);

	/// Zwroc dlugosc mapy cieni/ tekstury.
	GLuint GetShadowWidth()
	{
		return shadowWidth;
	}

	/// Zwroc wysokosc mapy cieni/ tekstury.
	GLuint GetShadowHeight()
	{
		return shadowHeight;
	}

	/// Destruktor.
	~ShadowMap();

protected:
	GLuint FBO;          // Identyfikator bufora ramki (ang.: Frame Buffer Object).
	GLuint shadowMap;    // Identyfikator mapy cieni (identyfikator tekstury).
	
	GLuint shadowWidth;  // Dlugosc mapy cieni, ¿eby pasowa³a do g³ównej ramki.
	GLuint shadowHeight; // Wysokosc mapy cieni, ¿eby pasowa³a do g³ównej ramki.
};

