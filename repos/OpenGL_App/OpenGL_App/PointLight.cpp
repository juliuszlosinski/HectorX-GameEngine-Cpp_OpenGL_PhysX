#include "PointLight.h"

/// Konstruktor.
PointLight::PointLight(): Light()
{
    // 1. Ustawienie pozycji zrodla swiata.
    position = glm::vec3(0.0f, 0.0f, 0.0f);

    // 2. Ustawienie wspolczynnikow tlumienia swiatla.
    // 1/(ax^2+bx+c)
    // 2.1 Sta³a ~ c.
    constant = 1.0f;

    // 2.2 Liniowy ~ b.
    linear = 0.0f;

    // 2.3 Eksponent ~ a.
    exponent = 0.0f;
}

/// Konstruktor.
PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
                       GLfloat aIntensity, GLfloat dIntensity,
                       GLfloat xPos, GLfloat yPos, GLfloat zPos,
                       GLfloat con, GLfloat lin, GLfloat exp) : Light(1024, 1024, red, green, blue, aIntensity, dIntensity)
{
    // 1. Ustawienie pozycji zrodla swiatla.
    position = glm::vec3(xPos, yPos, zPos);

    // 2. Ustawienie wspolczynnikow tlumienia swiatla.
    // 1/(ax^2+bx+c)
    // 2.1 Sta³a ~ c.
    constant = con;

    // 2.2 Liniowy ~ b.
    linear = lin;

    // 2.3 Eksponent ~ a.
    exponent = exp;
}

/// Uzywanie swiatla.
void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
                          GLuint diffuseIntensityLocation, GLuint positionLocation,
                          GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation)
{
    // 1. Ustawienie uniformu dla koloru.
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);

    // 2. Ustawienie uniformu dla intesywnosci swiatla otoczenia.
    glUniform1f(ambientIntensityLocation, ambientIntensity);

    // 3. Ustawienie uniformu dla intensywnosci swiatla rozproszenia.
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);

    // 4. Ustawienie uniformu dla pozycji zrodla swiatla.
    glUniform3f(positionLocation, position.x, position.y, position.z);

    // 5. Ustawienie uniformu dla stalej ~ c.
    glUniform1f(constantLocation, constant);

    // 6. Ustawienie uniformu dla liniowej ~ bx.
    glUniform1f(linearLocation, linear);

    // 7. Ustawienie uniformu dla eksponenty ~ ax^2.
    glUniform1f(exponentLocation, exponent);
}

/// Destruktor.
PointLight::~PointLight()
{

}