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
PointLight::PointLight(GLfloat shadowWidth, GLfloat shadowHeight,
                       GLfloat near, GLfloat far,
                       GLfloat red, GLfloat green, GLfloat blue,
                       GLfloat aIntensity, GLfloat dIntensity,
                       GLfloat xPos, GLfloat yPos, GLfloat zPos,
                       GLfloat con, GLfloat lin, GLfloat exp) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity)
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

    // 3. Ustawienie odleglosc na jak daleko kamera moze patrzec.
    farPlane = far;

    // 4. Obliczenie proporcji.
    float aspect = (float)shadowWidth / (float)shadowHeight;

    // 5. Ustawienie projekcji swiatla.
    lightProj = glm::perspective(glm::radians(90.0f), aspect, near, far);

    // 6. Utworzenie mapy cieniowania.
    shadowMap = new OmniShadowMap();

    // 7. Inicjalizacja mapy cieniowania.
    shadowMap->Init(shadowWidth, shadowHeight);
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

/// Zwrocenie 6 puntkow widzenia/ stron kamery pomnozonych przez projekcje (6 stron: projekcja x widok_f).
/// Kazdy kierunek w który kamera patrzy, a patrzy one w 6 strony.
/// Prawa: +x, Lewa: -x, Gora: +y, Dol: -y, Tyl: +z, Przod: -z
std::vector<glm::mat4> PointLight::CalculateLightTransform()
{
    // 1. Utworzenie pustego wektora.
    std::vector<glm::mat4> lightMatrices;

    // 2. Dodawnie macierzy transformacji (projekcja x widok).
    // +x
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    // -x
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    // +y
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    // -y
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
    // +z
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    // -z
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

    // 3. Zwrocenie wektora z macierzami transformacji.
    return lightMatrices;
}

/// Uzyskanie odleglosc na jaka widzi kamera.
GLfloat PointLight::GetFarPlane()
{
    return farPlane;
}
    
/// Zwrocenie pozycji swiatla.
glm::vec3 PointLight::GetPosition()
{
    return position;
}

/// Destruktor.
PointLight::~PointLight()
{

}