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

	// Zwrocenie nacisnietych badz nie, klawiszy (numery).
	bool* getKeys()
	{
		return keys;
	}

	// Dlugosc bufora.
	GLfloat getBufferWidth()
	{
		return bufferWidth;
	}

	// Wysokosc bufora.
	GLfloat getBufferHeight()
	{
		return bufferHeight;
	}

	// Uzyskanie wartosci x.
	GLfloat getXChange();

	// Uzyskanie wartosci y.
	GLfloat getYChange();

	// Czy okna powinno sie zamknac.
	bool getShouldClose()
	{
		return glfwWindowShouldClose(mainWindow);
	}

	// Zamiana buforow.
	void SwapBuffers()
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

	GLfloat lastX;	 // Ostatnia wartosc x.
	GLfloat lastY;	 // Ostatnia wartosc y.
	GLfloat xChange; // Roznica miedzy ostatnia wartoscia x a terazniejsza.
	GLfloat yChange; // Roznica miedzy ostatnia wartoscia y a terazniejsza.
	bool mousedFirstMoved; // Pierwsze poruszenie myszka ~ inicjalizacja (ustawienie pocz¹tkowej konfiguracji).

	bool keys[1024]; // Klawiatura.

	void createCallbacks(); // Inicjalizacja obslugi klawiatury oraz jaka funkcja bedzie wywolywana (ta ponizej bedzie).

	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode); // Obs³uga klawiszy ~ Na tym bedzie call back od GLFW.
										// Id klawisza  ___  Nacisniete czy zwolnione __

	static void handleMouse(GLFWwindow* window, double xPos, double yPos); // Obs³uga myszki.
};

