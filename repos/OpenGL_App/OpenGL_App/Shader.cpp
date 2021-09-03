#include "Shader.h"

// CreateFromString(...) -> CompileShader(...) -> 2x AddShader(...) -> Mamy program z shader'ami oraz lokalizacje uniform'ow (projekcji oraz modelu). 
// CreateFromFiles(...) -> 2 x ReadFile(...) -> CompileShader(...) -> 2x AddShader(...) -> Mamy program z shader'ami oraz lokalizacje uniform'ow (projekcji oraz modelu).

/// Konstruktor
Shader::Shader()
{
	// 1. Inicjalizacja wszystkich pol do zera.
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

/// Uzywaj shader'a.
void Shader::UseShader()
{
	glUseProgram(shaderID);
}

/// Wyczyœæ shader.
void Shader::ClearShader()
{
	// 1. Usuwanie programu.
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
	}

	// 2. Czyszczenie zmiennych z lokalizacjami uniformow w shaderze.
	uniformModel = 0;
	uniformProjection = 0;
}

/// Utworzenie Shader'a z normalnych ³añcuchów znaków.
void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) // Utworz shader z ³¹ñcucha znaków.
{
	CompileShader(vertexCode, fragmentCode);
}

/// Uzyskanie ³añcucha znaków z pliku.
std::string Shader::ReadFile(const char* fileLocation)
{
	// 1. Lancuch znakow z zawartoscia.
	std::string content;

	// 2. Obiekt do czytania z pliku.
	std::ifstream fileStream(fileLocation, std::ios::in);

	// 3. Sprawdzenie czy plik zosta³ otworzony.
	if (!fileStream.is_open())
	{
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	// 4. Sprawdzanie czy nie dotarlismy do konca pliku oraz dodanie do kontentu.
	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	// 5. Zamkniecie obiektu do czytania pliku.
	fileStream.close();

	// 6. Zwrocenie ciagu otrzymanego ciagu znakow.
	return content;
}

/// Utworzenie shadera z plików.
void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	/// 1. Uzyskanie kodu zrodlowego shadera wierzcholkow.
	std::string vertexString = ReadFile(vertexLocation);
	const char* vertexCode = vertexString.c_str();

	/// 2. Uzyskanie kodu zrodlowego shader fragmentow.
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* fragmentCode = fragmentString.c_str();

	//std::cout << vertexString << "\n" << fragmentString;

	/// 3. Utworzenie programu z Shaderami.
	CompileShader(vertexCode, fragmentCode);
}

/// Kompilacja oraz utworzenie programu z shader'ami.
void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) // Kompiluj shader.
{
	// 1. Utworzenie pustego programu.
	shaderID = glCreateProgram();

	// 1.1 Sprawdzenie czy zosta³ dobrze stworzony.
	if (!shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	// 2. Za³¹czenie Vertex Shader do programu.
	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);

	// 3. Za³¹czenie Fragment Shader do programu.
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	// 4. Powi¹zanie ze sob¹ wszystkich shaderów oraz stworzenie z nich pliku wykonywalnego dla karty graficznej (poniewa¿ programy s¹ na karcie a my tylko zmieniamy ich treœæ).
	glLinkProgram(shaderID);

	// 5. Sprawdzaczenie czy proces powi¹zywania shaderów siê powiód³.
	GLchar eLog[1024] = { 0 };
	GLint result = 0;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s' \n", eLog);
		return;
	}

	// 6. Walidacja programu czyli sprawdzanie czy utworzony program jest zgodny z wczesniej utworznym kontekstem.
	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s' \n", eLog);
		return;
	}

	/// * Uzyskanie lokalizacji uniformu zmiennych.
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformAmbientColour = glGetUniformLocation(shaderID, "directionalLight.colour");
	uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
}

/// Dodanie shader'a do programu z shader'ami.
void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) // Za³¹cz shader do programu.
{
	// 1. Utworzenie pustego shader'a o okreœlonym typie oraz uzyskanie jego identyfikatora.
	GLuint theShader = glCreateShader(shaderType);

	// 2. Przypisanie kodu.
	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	// 3. Za³¹czenie kodu.
	glShaderSource(theShader, 1, theCode, codeLength);

	// 4. Kompilacja shadera.
	glCompileShader(theShader);

	// 5. Sprawdzanie b³êdów.
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s' \n", shaderType, eLog);
		return;
	}

	// 5. Za³¹czenie shadera do programu.
	glAttachShader(theProgram, theShader);
}

/// Zwrocenie lokalizacji uniformu macierzy modelu.
GLuint Shader::GetModelLocation() // Uzyskaj lokalizacje modelu.
{
	return uniformModel;
}

/// Zwrocenie lokalizacji uniformu macierzy widoku.
GLuint Shader::GetViewLocation() // Uzyskaj lokalizacje macierzy widoku.
{
	return uniformView;
}

/// Zwrocenie lokalizacji uniformu macierzy projekcji.
GLuint Shader::GetProjectionLocation() // Uzyskaj lokalizacje projekcji.
{
	return uniformProjection;
}

/// Zwrocenie lokalizacji uniformu koloru.
GLuint Shader::GetAmbientColourLocation() // Uzyskaj lokalizacje.
{
	return uniformAmbientColour;
}

/// Zwrocenie lokalizacji moc oswietlenia otoczenia.
GLuint Shader::GetAmbientIntensityLocation() // Uzyskaj lokalizacje.
{
	return uniformAmbientIntensity;
}

/// Destruktor.
Shader::~Shader()
{
	ClearShader();
}