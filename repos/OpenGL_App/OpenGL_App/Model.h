#pragma once

/// Za³¹czenie nag³ówków
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	/// Konstuktor.
	Model();

	/// Ladowanie modelu.
	void LoadModel(const std::string& fileName);

	/// Renderuj model.
	void RenderModel();

	/// Czysc model.
	void ClearModel();

	/// Destruktor.
	~Model();

private:

	/// Zaladoj wezel.
	void LoadNode(aiNode* node, const aiScene* scene);

	/// Zaladoj siatke.
	void LoadMesh(aiMesh* mesh, const aiScene* scene);

	/// Zalodoj materialy/ tekstury.
	void LoadMaterials(const aiScene* scene);

	std::vector<Mesh*> meshList; // Lista siatek.
	std::vector<Texture*> textureList; // Lista tekstur.
	std::vector<unsigned int> meshToTex; // Wskazywanie, ktore tekstury uzywac, zeby nie powtarzac ich w innej liscie.
};

