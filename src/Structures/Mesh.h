#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <vector>
#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>

namespace lucy {
	struct Mesh {
		lgl::VertexArray* vertexarray = nullptr;
		lgl::VertexBuffer* vertexbuffer = nullptr;
		lgl::IndexBuffer* indexbuffer = nullptr;

		int vertexcount = 0;
		int indexcount = 0;

		lgl::Primitive primitive = lgl::TRIANGLE;

		Mesh() {}
		~Mesh();
		Mesh(aiMesh* ai_mesh);
		void Load(const std::string& filename, const std::string mesh_name);
	};
}