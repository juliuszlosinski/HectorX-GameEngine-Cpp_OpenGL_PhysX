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

	void CreateFromString(const char* vertexCode, const char* fragmentCode); // Utworz shader z ³¹ñcucha znaków.
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLcation); // Utworzenie shadera z plików.

	std::string ReadFile(const char* fileLocation); // Czytanie z pliku.

	GLuint GetProjectionLocation(); // Uzyskaj lokalizacje projekcji.
	GLuint GetModelLocation(); // Uzyskaj lokalizacje modelu.

	void UseShader(); // U¿yj shader'a.
	void ClearShader(); // Wyczyœæ shader.

	~Shader(); // Destruktor.
private:
	GLuint shaderID; // Identyfikator shader'a.
	GLuint uniformProjection; // Identyfikator uniformu projekcji.
	GLuint uniformModel; // Identyfikator uniformu modelu.

	void CompileShader(const char* vertexCode, const char* fragmentCode); // Kompiluj shader.
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType); // Za³¹cz shader do programu.
};

