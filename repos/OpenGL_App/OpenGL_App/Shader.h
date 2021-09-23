#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "CommonValues.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader
{
public:
	Shader(); // Konstruktor.

	/// CreateFromString(...) -> CompileShader(...) -> 2x AddShader(...) -> Mamy program z shader'ami oraz lokalizacje uniform'ow (projekcji oraz modelu). 
	/// CreateFromFiles(...) -> 2 x ReadFile(...) -> CompileShader(...) -> 2x AddShader(...) -> Mamy program z shader'ami oraz lokalizacje uniform'ow (projekcji oraz modelu).

	void CreateFromString(const char* vertexCode, const char* fragmentCode); // Utworz shader z ³¹ñcucha znaków.
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLcation); // Utworzenie shadera z plików.
	void CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLcation); // Utworzenie shadera z plików.


	std::string ReadFile(const char* fileLocation); // Czytanie z pliku.

	GLuint GetProjectionLocation(); // Uzyskaj lokalizacje macierzy projekcji.
	GLuint GetModelLocation(); // Uzyskaj lokalizacje macierzy modelu.
	GLuint GetViewLocation(); // Uzyskaj lokalizacje macierzy widoku.
	
	GLuint GetAmbientIntensityLocation(); // Uzyskaj lokalizacje moc oswietlenia otoczenia.
	GLuint GetAmbientColourLocation(); // Uzyskaj lokalizacje koloru otoczenia.

	GLuint GetDiffuseIntensityLocation(); // Uzyskaj lokalizacje mocy oswietlenia rozproszonego.
	GLuint GetDirectionLocation(); // Uzykaj lokalizacje kierunku swiatla rozproszonego.

	GLuint GetSpecularIntensityLocation(); // Uzyskaj lokalizacje mocy oswietlenia.
	GLuint GetShininessLocation(); // Uzyskaj lokalizacje wspolczynnika skupienia mocy.
	
	GLuint GetEyePosition(); // Uzyskaj lokalizacje uniformu dla polozenia kamery.

	GLuint GetOmniLightPosLocation(); // Uzyskaj lokalizacje pozycji swiatla.
	GLuint GetFarPlaneLocation(); // Uzyskaj lokalizacje odleglosci na jaka moze patrzec kamera.

	void UseShader(); // U¿yj shader'a.
	void ClearShader(); // Wyczyœæ shader.

	void SetDirectionalLight(DirectionalLight* dLight); // Ustawienie swiatla kierunkowego.
	void SetPointLights(PointLight* pLight, unsigned int lightCount); // Ustawienie swiatel miejscowych.
	void SetSpotLights(SpotLight* sLight, unsigned int lightCount); // Ustawienie swiatel reflektorowych.
	void SetTexture(GLuint textureUnit); // Ustawienie tekstury.
	void SetDirectionalShadowMap(GLuint textureUnit); // Ustawienie kierunkowej mapy cieniowania.
	void SetDirectionalLightTransform(glm::mat4* lTransform); // Ustawienie macierzy patrzenia swiatla kierunkowego.
	void SetLightMatrices(std::vector<glm::mat4> lightMatrices); // Ustaw macierze transformacji swiatla.

	~Shader(); // Destruktor.
private:
	int pointLightCount; // Ilosc swiatel punktowych.
	int spotLightCount;  // Ilosc swiatel reflektorowych.

	GLuint shaderID; // Identyfikator shader'a.
	GLuint uniformProjection; // Identyfikator uniformu projekcji.
	GLuint uniformModel; // Identyfikator uniformu modelu.
	GLuint uniformView; // Identyfikator macierzy widoku.
	GLuint uniformEyePosition; // Identyfikator uniformu pozycji kamery.

	GLuint uniformSpecularIntensity; // Identyfikator polozenia mocy oswietlenia.
	GLuint uniformShininess; // Identyfikator uniformu mocy skupienia swiatla.

	GLuint uniformTexture; // Identyfikator polozenia tekstury.
	GLuint uniformDirectionalLightTransform; // Identyfikator macierzy swiatla kierunkowego.
	GLuint uniformDirectionalShadowMap; // Identyfikator mapy cieniowania.

	GLuint uniformOmniLightPos; // Identyfikator pozycji pozycji wielokierunkwego swiatla.
	GLuint uniformFarPlane; // Identyfikator polozenia odleglosci na ja widzi kamera.

	GLuint uniformLightMatrices[6]; // Identyfikator polozenia macierzy transformacji swiatla (6 stron: lewa, prawa, gora, dol, przod, tyl).

	struct
	{
		GLuint uniformColour; // Kolor swiatla.
		GLuint uniformAmbientIntensity; // Intensywnosc otoczenia.
		GLuint uniformDiffuseIntensity; // Intensywnosc rozproszenia.

		GLuint uniformDirection; // Kierunek swiatla.
	} uniformDirectionalLight;

	GLuint uniformPointLightCount; // Identyfikator ilosc swiatel punktowych.

	struct
	{
		GLuint uniformColour; // Kolor swiatla.
		GLuint uniformAmbientIntensity; // Intensywnosc otoczenia.
		GLuint uniformDiffuseIntensity; // Intensywnosc rozproszenia.

		// 1/(ax^2+bx+c)
		GLuint uniformPosition; // Pozycja swiatla.
		GLuint uniformConstant; // Stala ~ c.
		GLuint uniformLinear;	// Liniowy ~ b.
		GLuint uniformExponent; // Exponent ~ a.
	} uniformPointLight[MAX_POINT_LIGHTS];

	GLuint uniformSpotLightCount; // Identyfikator polozenia ilosci swiatel reflektorowych.

	struct
	{
		GLuint uniformColour; // Kolor swiatla.
		GLuint uniformAmbientIntensity; // Intensywnosc otoczenia.
		GLuint uniformDiffuseIntensity; // Intensywnosc rozproszenia.

		// 1/(ax^2+bx+c)
		GLuint uniformPosition; // Pozycja swiatla.
		GLuint uniformConstant; // Stala ~ c.
		GLuint uniformLinear;	// Liniowy ~ b.
		GLuint uniformExponent; // Exponent ~ a.

		GLuint uniformDirection; // Kierunek swiecenia swiatla.
		GLuint uniformEdge; // Kat swiecenia.
	} uniformSpotLight[MAX_SPOT_LIGHTS];

	void CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode); // Kompiluj shader.
	void CompileShader(const char* vertexCode, const char* fragmentCode); // Kompiluj shader.
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType); // Za³¹cz shader do programu.

	void CompileProgram(); // Kompilacja programu.
};

