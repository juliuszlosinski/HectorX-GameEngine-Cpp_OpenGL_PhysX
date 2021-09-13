#pragma once

// Za³¹czenie pliku nag³ówkowego z GLEW.
#include <GL\glew.h>

// Za³¹czenie pliku nag³ówkowego z macierzemi z GLM.
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

// Za³¹czenie pliku nag³ówkoego z GLFW.
#include <GLFW\glfw3.h>

class Camera
{
public:
	/// Konstruktor.
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	/// Kontrol za pomoca klawiatury.
	void keyControl(bool* keys, GLfloat deltaTime);

	/// Kontrola za pomoca myszki (obrot).
	void mouseControl(GLfloat xChange, GLfloat yChange);

	/// Uzyskanie pozycji kamery.
	glm::vec3 getCameraPosition();

	/// Obliczanie macierzy widoku, ¿ebyœmy mogli widzieæ rzeczy z perspektywy kamery.
	glm::mat4 calculateViewMatrix();

	/// Destruktor.
	~Camera();
private:
	glm::vec3 position; // Pozycja kamery.
	glm::vec3 front; // Okresla kierunek, ktory jest na przeciwko kamery.
	glm::vec3 up; // Okresla kierunek, ktory jest do gory od kamery.
	glm::vec3 right; // Okresla kierunek, ktory jest na prawo od kamery.
	glm::vec3 worldUp; // Punkt referencyjny do, którego bêdziemy sie odnosiæ np. niebo.

	// Te wartosci beda aktualizowaly front oraz right.
	GLfloat yaw;	// K¹t odchylenia -> na prawo lub lewo (oœ Y).
	GLfloat pitch;	// K¹t pochylenia -> do góry lub na dó³ (oœ X).

	GLfloat moveSpeed; // Szybkosc poruszania siê.
	GLfloat turnSpeed; // Szybkosc obrotu.

	// Aktualizowanie wartosci.
	void update();
};

