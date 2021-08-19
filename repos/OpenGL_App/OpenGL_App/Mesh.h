#pragma once

#include <GL\glew.h>

class Mesh
{
public:
	Mesh(); // Konstruktor siatki.

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices); // Tworzenie siatki (przesy³amy dane).
	void RenderMesh(); // Rysowanie siatki.
	void ClearMesh();  // Usuwanie z karty graficznej.

	~Mesh(); // Destruktor siatki.

private:
	GLuint VAO; // Zdefiniowanie Vertex Array Object -> tak zwany "Profil".
	GLuint VBO; // Zdefiniowanie Vertex Buffer Object -> przechowywanie danych z wierzcho³kami.
	GLuint IBO; // Zdefiniowanie Index Buffer Object -> przechowywanie indeksów.
	GLsizei indexCount; // Iloœæ indeksów/ elementów.
};

