#pragma once

#include <stdio.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	Window(); // Konstruktor.

	Window(GLint windowWidth, GLint windowHeight); // Konstruktor.

	int Initialise(); // Inicjalizacja okna.

	GLfloat getBufferWidth() // Dlugosc bufora.
	{
		return bufferWidth;
	}

	GLfloat getBufferHeight() // Wysokosc bufora.
	{
		return bufferHeight;
	}

	bool getShouldClose() // Czy okna powinno sie zamknac.
	{
		return glfwWindowShouldClose(mainWindow);
	}

	void SwapBuffers() // Zamiana buforow.
	{
		glfwSwapBuffers(mainWindow);
	}

	~Window(); // Destruktor.
private:
	GLFWwindow* mainWindow; // Wskaznik do okna.
	GLint width; // Dlugosc okna.
	GLint height; // Wysokosc okna.
	GLint bufferWidth; // Dlugosc bufora.
	GLint bufferHeight; // Szerokosc bufora.
};

