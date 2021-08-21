#include "Window.h"

/// Konstruktor.
Window::Window()
{
	// 1. Ustawienie parametrow wielkosci okna.
	width = 800;
	height = 600;
	
	// 2. Ustawienie klawiszy na nie wcisniete.
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	// 3. Ustawienie poczatkowej zmiany.
	xChange = 0.0f;
	yChange = 0.0f;
}

/// Przeci¹zanie konstruktora.
Window::Window(GLint windowWidth, GLint windowHeight)
{
	// 1. Ustawienie parametrow wielkosci okna.
	width = windowWidth;
	height = windowHeight;

	// 2. Ustawienie klawiszy na nie wcisniete.
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	// 3. Ustawienie poczatkowej zmiany.
	xChange = 0.0f;
	yChange = 0.0f;
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

	/// 6. Obs³ugiwanie klawiatury oraz myszki.
	createCallbacks();

	/// 7. Wymazanie kurosora z ekranu.
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// 8. Pozwolenie na u¿ycie nowoczesnych rozszerzeñ.
	glewExperimental = GL_TRUE;

	// 9. Inicjalizacja GLEW (biblioteki oraz wszystkich funkcji, które tam s¹).
	if (glewInit() != GLEW_OK)
	{
		// 8.1 Wypisanie komunikatu o niepowodzeniu.
		printf("GLEW initialization failed!");

		/// 8.2 Zniszczenie obecnego utworzonego wczesniej okna.
		glfwDestroyWindow(mainWindow);

		/// 8.3 Zwrocenie zainicjalizowanych wczesniej zasobow przez GLFW.
		glfwTerminate();

		/// 8.4 Zgloszenie bledu.
		return 1;
	}

	// 10. Aktywowanie bufora glebokosci, zeby moc pozniej mowic, ktore sciany sa dalej.
	glEnable(GL_DEPTH_TEST);

	// 11. Ustawienie rozmiaru portu widoku (Viewport).
	glViewport(0, 0, bufferWidth, bufferHeight);

	// 12. Ustawienie uzytkownika dla okna.
	glfwSetWindowUserPointer(mainWindow, this);
}

/// Inicjalizacja obslugi klawiatury ~ ustawienie call back'ow na odpowiednia funkcje, ze by ja wywolywala.
void Window::createCallbacks()
{
	// 1. Kiedy klawisz jest nacisniety na tym oknie to wywolaj funkcje obslugujaca klawiature.
	glfwSetKeyCallback(mainWindow, handleKeys);

	// 2. Kiedy bedziemy poruszac myszka to odpowiednia funkcja (handleMouse) zostanie wywolana.
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

/// Obslugiwanie klawiatury ~ ona zostanie wywolana przez call back.
void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) // Obs³uga klawiszy ~ Na tym bedzie call back od GLFW.
{
	// 1. Uzyskanie okna.
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	// 2. Zamknij okna jezeli uzytkownik nacisnal escape.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	// 3. Sprawdzenie czy jakis klawisz zostal nacisniety.
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("Pressed: %d\n", key);
		}
		else if(action==GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("Released: %d\n", key);
		}
	}
}

/// Obs³ugiwanie myszki.
void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	// 1. Uzyskanie okna.
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	// 2. Sprawdzenie czy je pierwsze poruszenie myszk¹.
	if (theWindow->mousedFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mousedFirstMoved = false;
	}

	// 3. Uzyskanie roznicy miedzy ostatnia wartoscia x a terazniejsza.
	theWindow->xChange = xPos - theWindow->lastX;

	// 4. Uzyskanie roznicy miedzy ostatnia wartoscia y a terazniejsza.
	theWindow->yChange = theWindow->lastY - yPos;

	// 5. Ustawienie ostatniej pozycji x.
	theWindow->lastX = xPos;

	// 6. Ustawienie ostatniej pozycji y.
	theWindow->lastY = yPos;

	//printf("x: %.6f, y: %.6f\n", theWindow->xChange, theWindow->yChange);
}

/// Uzyskanie wartosci x.
GLfloat Window::getXChange()
{
	// 1. Uzyskanie wartosci zamiany oraz jej wyzerowanie.
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

/// Uzyskanie wartosci y.
GLfloat Window::getYChange()
{
	// 1. Uzyskanie wartosci zamiany oraz jej wyzerowanie.
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

/// Destruktor.
Window::~Window()
{
	/// 1. Zniszczenie obecnego utworzonego wczesniej okna.
	glfwDestroyWindow(mainWindow);

	/// 2. Zwrocenie zainicjalizowanych wczesniej zasobow przez GLFW.
	glfwTerminate();
}