#include "ShadowMap.h"

/// Konstruktor.
ShadowMap::ShadowMap()
{
	// 1. Inicjalizacja pol.
	FBO = 0;
	shadowMap = 0;
}

/// Inicjalizacja.
bool ShadowMap::Init(GLuint width, GLuint height)
{
	// 1. Ustawianie parametrow.
	shadowWidth = width;
	shadowHeight = height;

	// 2. Generowanie bufora ramki.
	glGenFramebuffers(1, &FBO);

	// 3. Utworzenie tekstury.
	glGenTextures(1, &shadowMap);

	// 4. Ustawienie tekstury jako roboczej.
	glBindTexture(GL_TEXTURE_2D, shadowMap);

	// 5. Ustawienie pustej tekstury ~ uzyskiwanie wartosci glebokosci od 0.0 do 1.0 bazujc na znormalizowanych kordynatach.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	// 6. Owijanie tekstury (jest ustawiane powtarzanie).
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float bColour[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, bColour);

	// 7. Ustawianie filtrow (jak ma sie zachowywac tekstura w kontekscie odleglosci).
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 8. Ustawienie bufora ramki roboczej.
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// 9. Polaczenie tekstury z buforem ramki.
	// Kiedy scena bedzie renderowana, to zostanie ona do tej tekstury.
	// GL_DEPTH_ATTACHMENT ~ Wartosci glebi beda wpisywane do tekstury po wyrenderowaniu sceny.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

	// 10. Nie odczytujemy wartosci koloru z za³¹cznika kolorów.
	glDrawBuffer(GL_NONE);

	// 11. Nie zapisujemy wartosci koloru z za³¹cznika kolorów.
	glReadBuffer(GL_NONE);

	// 12. Sprawdzanie czy wszystko siê powiod³o.
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		// 12.1 Nie powiodlo sie!
		printf("Framebuffer Error: %i\n", status);
		return false;
	}

	// 13. Zdjecie roboczego bufora ramki, ustawienie na tego glownego ze scena.
	// 0 ~ To jest na, którmy rysujemy i bêdzie on zamieniony kiedy wywolamy SwapBuffers().
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 14. Powiodlo sie!
	return true;
}

/// Wpisywanie | Rysowanie na obecnym buforze ramki.
void ShadowMap::Write()
{
	// 1. Rysowanie/ wpisywanie do obecnego bufora ramki.
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

/// Czytanie wartosci.
void ShadowMap::Read(GLenum textureUnit)
{
	// 1. Aktywowanie jednostki tekstury, do ktorej pozniej sampler bedzie mial dostep w shaderze.
	glActiveTexture(textureUnit);

	// 2. Przeslanie tekstury/ powiazanie tekstury.
	glBindTexture(GL_TEXTURE_2D, shadowMap);
}

/// Destruktor.
ShadowMap::~ShadowMap()
{
	if (FBO)
	{
		// 1. Usuniecie bufora ramki.
		glDeleteFramebuffers(1, &FBO);
	}

	if (shadowMap)
	{
		// 2. Usuniecie mapy cieniowania/ tekstury.
		glDeleteTextures(1, &shadowMap);
	}

}