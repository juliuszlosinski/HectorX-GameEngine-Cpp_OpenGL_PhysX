#include "Camera.h"

/// Konstruktor.
Camera::Camera()
{

}

/// Konstruktor.
Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	// 1. Ustawianie pocz¹tkowych wartosci pol.
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

/// Kontrola kamery za pomoca przyciskow.
void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;
	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

/// Obliczenie macierzy widoku, zebysmy mogli widziec rzeczy relatywnie do kamery.
glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

/// Uzyskanie lokalizacji kamery.
glm::vec3 Camera::getCameraPosition()
{
	return position;
}

/// Uzyskanie frontu/ kierunku kamery.
glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

/// Aktualizowanie parametrow kamery (jest wykonywane tylko wtedy kiedy poruszymy myszka).
void Camera::update()
{
	// 1. Obliczanie nowych parametrów naszego kierunku patrzenia.
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	// 2. Obliczanie prawej strony.
	right = glm::normalize(glm::cross(front, worldUp));

	// 3. Obliczanie góry.
	up = glm::normalize(glm::cross(right, front));
}

/// Obrot kamery.
void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	// 1. Ustawianie parametrow.
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	// 2. Aktualizowanie kierunku.
	update();
}

/// Destruktor.
Camera::~Camera()
{

}