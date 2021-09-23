#pragma once
#include "Light.h"

// Zaladowanie naglowka z wektorem.
#include <vector>

#include "OmniShadowMap.h"

class PointLight : public Light
{
public:
    /// Konstruktor.
    PointLight();

    /// Konstruktor.
    PointLight(GLfloat shadowWidth, GLfloat shadowHeight,
               GLfloat near, GLfloat far,
               GLfloat red, GLfloat green, GLfloat blue, 
               GLfloat aIntensity, GLfloat dIntensity,
               GLfloat xPos, GLfloat yPos, GLfloat zPos, 
               GLfloat con, GLfloat lin, GLfloat exp);

    /// Uzywanie swiatla.
    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
                  GLuint diffuseIntensityLocation, GLuint positionLocation,
                  GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);
    
    /// Oblicz transformacje swiatla (6 stron: projekcja x widok).
    std::vector <glm::mat4> CalculateLightTransform();

    /// Zwroc odleglosc na jak daleko kamera moze widziec.
    GLfloat GetFarPlane();

    /// Uzyskanie pozycji swiatla.
    glm::vec3 GetPosition();

    /// Destruktor.
    ~PointLight();

protected:
    glm::vec3 position; // Pozycja zrodla swiatla.
    
    // Wspó³czynniki odw. równania kwadratowego do obliczenia wsp³óczynnika t³umienia œwiat³a.
    // 1/(ax^2 + bx + c) 
    GLfloat constant; // Stala ~ c.
    GLfloat linear; // Liniowy ~ b.
    GLfloat exponent; // Eksponent ~ a.

    GLfloat farPlane; // Odleglosc jak daleko kamera moze widziec.
};

