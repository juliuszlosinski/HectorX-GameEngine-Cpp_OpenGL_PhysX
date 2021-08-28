#include "Mesh.h"

// Podstawowy konstruktor siatki.
Mesh::Mesh()
{
	// Utworzenie podstawowej konfiguracji (wszystko jest NULL).
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

// Utworzenie siatki.
void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices) // Tworzenie siatki (przesy³amy dane).
{
	// 1. Przypisanie iloœci indeksów do pola z iloœci¹ indeksów.
	indexCount = numOfIndices;

	// 2. Utworzenie VAO.
	glGenVertexArrays(1, &VAO);

	// 3. Ustawienie VAO jako roboczego (binding).
	glBindVertexArray(VAO);

	/// 4.Utworzenie bufora IBO.
	glGenBuffers(1, &IBO);

	/// 5. Ustawienie bufora IBO jako roboczego.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	/// 6. W³o¿enie danych do powi¹zanego bufora IBO.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	// 7.. Utworzenie VBO (tworzy VBO wewn¹trz VAO).
	glGenBuffers(1, &VBO);

	/// 8. Ustawienie VBO jako roboczego (binding).
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 9. Wlozenie danych wierzcho³ków do buffora VBO, który jest powi¹zany.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * numOfVertices, vertices, GL_STATIC_DRAW);

	// 10. Okreœlenie atrybutów wierzcho³ka.
	// [0] -> Id atrybutu.
	// [1] -> Ile wartosci ma wierzcho³ek (u nas s¹ 3).
	// [2] -> Jakiego typu s¹ wartoœci (u nas jest to float).
	// [3] -> Czy nale¿y jes normalizowaæ (u nas nie nale¿y).
	// [4] -> Co ile wartosci skakaæ (u nas jest to 0, bo nie skaczemy).
	// [5] -> Od którego wierzcho³ka zacz¹c (u nas jest to wierzcho³ek pierwszy).
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);



	/// 13. Zdjecie VBO z pozycji roboczej (unbinding)!!
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/// 14. Zdjecie IBO z pozycji roboczej (unbinding)!!
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// 12. Zdjecie VAO z pozycji roboczej (unbinding)!!
	glBindVertexArray(0);
}

// Rysowanie siatki.
void Mesh::RenderMesh()
{
	/// 1. Wybranie VAO (to co chcemy narysowac).
	glBindVertexArray(VAO);

	/// 2. Wybranie IBO.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	/// 3. Rysowanie
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	/// 4. Zwolnienie IBO.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/// 5. Zwolnienie VAO.
	glBindVertexArray(0);
}

// Zwolnienie pamiêcie na karcie graficznej.
void Mesh::ClearMesh()
{
	if (IBO != 0)
	{
		// 1. Zwolnienie bufora z indeksami w pamiêci GPU.
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}
	if (VBO != 0)
	{
		// 2. Zwolnienie bufora z wierzcho³kami w pamiêci GPU.
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
	if (VAO != 0)
	{
		// 3. Zwolnienie bufora z profilem w pamiêci GPU.
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	// 4. Wyzerowawnie zmiennej zawierajacej ilosc wierzcholkow.
	indexCount = 0;
}

// Destruktor.
Mesh::~Mesh()
{
	// 1. Zwolnienie pamieci na karcie graficznej.
	ClearMesh();
}