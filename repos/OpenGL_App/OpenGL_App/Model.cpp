#include "Model.h"

/// Konstruktor.
Model::Model()
{

}

/// Renderowanie modelu.
void Model::RenderModel()
{
	// 1. Przechodzenie przez wszystkie siatki.
	for (size_t i = 0; i < meshList.size(); i++)
	{
		// 1.1 Uzyskanie indeksu materialu.
		unsigned int materialIndex = meshToTex[i];

		// 1.2 Sprawdzenie czy material istnieje.
		if (materialIndex < textureList.size() && textureList[materialIndex])
		{
			// 1.2.1 Uzycie tekstury.
			textureList[materialIndex]->UseTexture();
		}

		// 1.2 Renderowanie siatki.
		meshList[i]->RenderMesh();
	}
}

/// Zaladowanie modelu.
void Model::LoadModel(const std::string& fileName)
{
	// 1. Utworzenie importera.
	Assimp::Importer importer;

	// 2. Utworzenie sceny.
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	//const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	// 3. Importowanie sceny.
	if (!scene)
	{
		printf("Model (%s) failed to load: %s",fileName, importer.GetErrorString());
		return;
	}

	// 4. Zaladownie wezla.
	LoadNode(scene->mRootNode, scene);

	// 5. Zaldaowanie materialu.
	LoadMaterials(scene);
}

/// Zalodowanie wezla.
void Model::LoadNode(aiNode* node, const aiScene* scene)
{
	// 1. Przechodzenie przez wszystkie siatki wezla.
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	// 2. Przechodzimy do dzieci wezla.
	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

/// Zaladowanie siatki.
void Model::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
	// 1. Utworzenie zbiornika na wierzcholki (pozycja, kordynaty tekstur, normale).
	std::vector<GLfloat> vertices;

	// 2. Utworzenie zbiornika na indeksy.
	std::vector<unsigned int> indices;

	// 3. Dodawanie pozycji, tekstur kordynatow oraz normali wierzcholkow do zbiornika na dane wierzcholkow (pozycja, kordynaty tekstur, normale).
	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		// 3.1 Dodanie pozycji.
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		
		// 3.2 Sprawdzenie s¹ kordynaty tekstury.
		if (mesh->mTextureCoords[0])
		{
			// 3.2.1 S¹!
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
		}
		else
		{
			// 3.2.2 Nie ma!
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}

		// 3.3 Dodawanie normali.
		vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z});
	}

	// 4. Przechodzenie przez sciany/ strony/ powierzchni (faces) zebysmy mogli dodac indeksy.
	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		// 4.1 Przechowanie powierzchni.
		aiFace face = mesh->mFaces[i];

		// 4.2 Dodawanie indeksow powierzchni do zbiornika
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	// 5. Utworzenie siatki.
	Mesh* newMesh = new Mesh();
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());

	// 6. Dodanie siatki do listy.
	meshList.push_back(newMesh);

	// 7. Uzyskanie indeksu mapowania.
	meshToTex.push_back(mesh->mMaterialIndex);
}

/// Zalodawnie materialow.
void Model::LoadMaterials(const aiScene* scene)
{
	// 1. Utworzenie tekstur.
	textureList.resize(scene->mNumMaterials);

	// 2. Przejscie przez wszystkie materialy/ tekstury.
	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		// 2.1 Uzyskanie materialu bezpoœrednio ze sceny.
		aiMaterial* material = scene->mMaterials[i];

		// 2.2 Przypisanie referencji poczatkowej.
		textureList[i] = nullptr;

		// 2.3 Sprawdzenie czy jest tekstura.
		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			// 2.4 Uzyskanie sciezki do tekstury.
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				// 2.4.1 Wyodrebnienie sciezki.
				int idx = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(idx + 1);
				std::string texPath = std::string("Textures/") + filename;

				// 2.5 Utworzenie tekstury.
				textureList[i] = new Texture(texPath.c_str());

				// 2.6 Zalodawnie tekstury oraz sprawdzenie czy sie powiodlo.
				if (!textureList[i]->LoadTexture())
				{
					// 2.6.1 Wypisanie komunikatu.
					printf("Failed to load texture at: %s\n", texPath);
					
					// 2.6.2 Usuniecie tekstury.
					delete textureList[i];
					textureList[i] = nullptr;
				}
			}
		}

		//* Brak tekstury = biale pole.
		if (!textureList[i])
		{
			textureList[i] = new Texture("Textures/plain.png");
			textureList[i]->LoadTextureA();
		}
	}
}

/// Czyszczenie modelu.
void Model::ClearModel()
{
	// 1. Przejscie przez wszystkie siatki oraz ich usuniecie
	for (size_t i = 0; i < meshList.size(); i++)
	{
		if (meshList[i])
		{
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}

	// 2. Przejscie przez wszystkie tekstury oraz ich usuniecie.
	for (size_t i = 0; i < textureList.size(); i++)
	{
		if (textureList[i])
		{
			delete textureList[i];
			textureList[i] = nullptr;
		}
	}
}

/// Destruktor.
Model::~Model()
{

}

