#pragma once

#include <Structures/Structures.h>
#include <unordered_map>
#include <Engine/UUID.h>
#include <Engine/AssetLoader.h>

namespace lucy {
	struct MaterialRegistry {
		std::unordered_map<uuid, Material> material_registry;

		MaterialRegistry() {}

		void Init();
		std::string AddMaterial(const Material& material, uuid id = GetID());
		std::string AddMaterial(aiMaterial* ai_material, uuid id = GetID());
		Material* GetMaterial(const std::string& id);
		std::string GetMaterialID(Material* material);
	};
}