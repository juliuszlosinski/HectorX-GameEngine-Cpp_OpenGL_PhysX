#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

class Shader
{
public:
	Shader(); // Konstruktor.

	/// CreateFromString(...) -> CompileShader(...) -> 2x AddShader(...) -> Mamy program z shader'ami oraz lokalizacje uniform'ow (projekcji oraz modelu). 
	/// CreateFromFiles(...) -> 2 x ReadFile(...) -> CompileShader(...) -> 2x AddShader(...) -> Mamy program z shader'ami oraz lokalizacje uniform'ow (projekcji oraz modelu).

	void CreateFromString(const char* vertexCode, const char* fragmentCode); // Utworz shader z ³¹ñcucha znaków.
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLcation); // Utworzenie shadera z plików.

	std::string ReadFile(const char* fileLocation); // Czytanie z pliku.

	GLuint GetProjectionLocation(); // Uzyskaj lokalizacje macierzy projekcji.
	GLuint GetModelLocation(); // Uzyskaj lokalizacje macierzy modelu.
	GLuint GetViewLocation(); // Uzyskaj lokalizacje macierzy widoku.
	GLuint GetAmbientIntensityLocation(); // Uzyskaj lokalizacje moc oswietlenia otoczenia.
	GLuint GetAmbientColourLocation(); // Uzyskaj lokalizacje koloru otoczenia.

	void UseShader(); // U¿yj shader'a.
	void ClearShader(); // Wyczyœæ shader.

	~Shader(); // Destruktor.
private:
	GLuint shaderID; // Identyfikator shader'a.
	GLuint uniformProjection; // Identyfikator uniformu projekcji.
	GLuint uniformModel; // Identyfikator uniformu modelu.
	GLuint uniformView; // Identyfikator macierzy widoku.
	GLuint uniformAmbientIntensity; // Identyfikator uniformu wspolczynnika oswietlenia otoczenia.
	GLuint uniformAmbientColour; // Identyfikator koloru otoczenia.

	void CompileShader(const char* vertexCode, const char* fragmentCode); // Kompiluj shader.
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType); // Za³¹cz shader do programu.
};

