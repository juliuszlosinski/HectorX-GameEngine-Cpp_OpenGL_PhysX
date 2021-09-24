#include "Texture.h"

/// Konstruktor.
Texture::Texture()
{
	// 1. Ustawianie poczatkowych parametrow.
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = NULL;
}

/// Konstrutkor.
Texture::Texture(const char* fileLoc)
{
	// 1. Ustawianie poczatkowych parametrow.
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = fileLoc;
}

/// Zaladowanie tekstury bez kanalu alpha.
bool Texture::LoadTexture()
{
	// 1. Ladaowanie obrazka oraz zapisywanie jego parametrow.
	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
	if (!texData)
	{
		printf("Failed to find: %s\n", fileLocation);
		return false;
	}

	// 2. Generowanie tekstury ~ uzyskanie identyfikatora tekstury.
	glGenTextures(1, &textureID);

	// 3. Ustawienie tekstury jako roboczej z danym identyfikatorem.
	glBindTexture(GL_TEXTURE_2D, textureID);

	// 4. Ustawianeie parametrow tekstury.

	// 4.1 Owijanie tekstury (jest ustawiane powtarzanie).
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 4.2 Ustawianie filtrow (jak ma sie zachowywac tekstura w kontekscie odleglosci).
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 5. Zaladowanie tekstory.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	// 6. Zdjecie tekstury z roboczej.
	glBindTexture(GL_TEXTURE_2D, 0);

	// 7. Zwolnienie ladownika obrazka.
	stbi_image_free(texData);

	return true;
}

/// Zaladowanie tekstury z kanalem alpha.
bool Texture::LoadTextureA()
{
	// 1. Ladaowanie obrazka oraz zapisywanie jego parametrow.
	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
	if (!texData)
	{
		printf("Failed to find: %s\n", fileLocation);
		return false;
	}

	// 2. Generowanie tekstury ~ uzyskanie identyfikatora tekstury.
	glGenTextures(1, &textureID);

	// 3. Ustawienie tekstury jako roboczej z danym identyfikatorem.
	glBindTexture(GL_TEXTURE_2D, textureID);

	// 4. Ustawianeie parametrow tekstury.

	// 4.1 Owijanie tekstury (jest ustawiane powtarzanie).
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 4.2 Ustawianie filtrow (jak ma sie zachowywac tekstura w kontekscie odleglosci).
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 5. Zaladowanie tekstory.
	/// OBRAZKI MUSZA MIEC ALPHA CHANNEL!!!
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	// 6. Zdjecie tekstury z roboczej.
	glBindTexture(GL_TEXTURE_2D, 0);

	// 7. Zwolnienie ladownika obrazka.
	stbi_image_free(texData);

	return true;
}

/// U¿ywanie tekstury.
void Texture::UseTexture()
{
	// 1. Aktywowanie tekstury (samplera).
	glActiveTexture(GL_TEXTURE1);

	// 2. Aktywowanie tekstury z danym identyfikatorem.
	glBindTexture(GL_TEXTURE_2D, textureID);
}

/// Czyszczenie tekstury.
void Texture::ClearTexture()
{
	// 1. Usuniecie tekstury.
	glDeleteTextures(1, &textureID);

	// 2. Czyszczenie parametrow.
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = NULL;
}

/// Destrutkor.
Texture::~Texture()
{
	// 1. Wyczyszczenie tekstury.
	ClearTexture();
}
