#include "Window.h"

/// Konstruktor.
Window::Window()
{
	// 1. Ustawienie parametrow wielkosci okna.
	width = 800;
	height = 600;
}

/// Przeci¹zanie konstruktora.
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

/// Inicjalizacja okna.
int Window::Initialise()
{
	/// 1. Inicjalizacja GLFW oraz sprawdzenie czy siê powiod³o.
	if (!glfwInit())
	{
		/// 1.1 Wydrukowanie komunikatu o niepowodzeniu.
		printf("GLFW initialization failed!");

		/// 1.2 Zwolnienie zainicjalizowanych zasobów.
		glfwTerminate();

		/// 1.3 Zg³oszenie Erroru.
		return 1;
	}

	/// 2. Ustawienie parametrów GLFW okna.
	/// 2.1 Wersja OpenGL.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	/// 2.2 Ustawienie kompatybilnosci z innymi wczeœniejszymi wersjami (BRAK).
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/// 2.3 Ustawienie kompatybilnosci z najnowszymi wersjami (JEST).
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/// 3. Utworzenie okna.
	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);

	/// 3.1 Sprawdzenie czy utworzenie okna sie powiodlo.
	if (!mainWindow)
	{
		/// 3.1.1 Wypisanie komunikatu o niepowodzeniu.
		printf("GLFW window creation failed!");

		/// 3.1.2 Zwrocenie zainicjalizowanych zasobow.
		glfwTerminate();

		/// 3.1.3 Zgloszenie bledu.
		return 1;
	}

	/// 4. Zdobycie informacji na temat rozmiaru buffora.
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	/// 5. Ustawienie kontekstu do u¿ycia dla GLEW, zwiazanie kontekstu z tym utworznym oknem.
	glfwMakeContextCurrent(mainWindow);

	// 6. Pozwolenie na u¿ycie nowoczesnych rozszerzeñ.
	glewExperimental = GL_TRUE;

	// 7. Inicjalizacja GLEW (biblioteki oraz wszystkich funkcji, które tam s¹).
	if (glewInit() != GLEW_OK)
	{
		// 7.1 Wypisanie komunikatu o niepowodzeniu.
		printf("GLEW initialization failed!");

		/// 7.2 Zniszczenie obecnego utworzonego wczesniej okna.
		glfwDestroyWindow(mainWindow);

		/// 7.3 Zwrocenie zainicjalizowanych wczesniej zasobow przez GLFW.
		glfwTerminate();

		/// 7.4 Zgloszenie bledu.
		return 1;
	}

	// 8. Aktywowanie bufora glebokosci, zeby moc pozniej mowic, ktore sciany sa dalej.
	glEnable(GL_DEPTH_TEST);

	// 8. Ustawienie rozmiaru portu widoku (Viewport).
	glViewport(0, 0, bufferWidth, bufferHeight);
}

/// Destruktor.
Window::~Window()
{
	/// 1. Zniszczenie obecnego utworzonego wczesniej okna.
	glfwDestroyWindow(mainWindow);

	/// 2. Zwrocenie zainicjalizowanych wczesniej zasobow przez GLFW.
	glfwTerminate();
}