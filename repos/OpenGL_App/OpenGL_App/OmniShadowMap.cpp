#include "OmniShadowMap.h"

/// Konstrutkor.
OmniShadowMap::OmniShadowMap() :ShadowMap()
{

}

/// Inicjalizacja.
bool OmniShadowMap::Init(GLuint width, GLuint height)
{
	// 1. Ustawienie dlugosci cienia.
	shadowWidth = width;

	// 2. Ustawienie wysokosci cienia.
	shadowHeight = height;

	// 3. Generowanie bufora ramki oraz otrzymanie jego identyfikatora.
	glGenFramebuffers(1, &FBO);

	// 4. Generowanie tekstury oraz otrzymanie jego identyfikatora.
	glGenTextures(1, &shadowMap);

	// 5. Ustawienie roboczej tekstury.
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);

	// 6. Przechodzenie przez kazda teksture w mapie szesciennej.
	for (size_t i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	}

	// 7. Ustawaianie parametrow tekstury.
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// 8. Ustawienie roboczego bufora ramki.
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// 9. Ustawienie miejsca wpisywania wartosci wynikowych po wyrenderowaniu sceny.
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0);

	// 10. Wylaczenie wpisywania kolorow.
	glDrawBuffer(GL_NONE);

	// 11. Wylaczenie czytania danych koloru.
	glReadBuffer(GL_NONE);

	// 12. Sprawdzanie czy wszystko siê powiod³o.
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		// 12.1 Nie powiodlo sie!
		printf("Framebuffer Error: %i\n", status);
		return false;
	}
	
	return true;
}

/// Wpisywanie | Rysowanie na obecnym buforze ramki.
void OmniShadowMap::Write()
{
	// 1. Rysowanie/ wpisywanie do obecnego bufora ramki.
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

/// Czytanie wartosci.
void OmniShadowMap::Read(GLenum textureUnit)
{
	// 1. Aktywowanie jednostki tekstury, do ktorej pozniej sampler bedzie mial dostep w shaderze.
	glActiveTexture(textureUnit);

	// 2. Przeslanie tekstury/ powiazanie tekstury.
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);
}

/// Desturktor.
OmniShadowMap::~OmniShadowMap()
{

}