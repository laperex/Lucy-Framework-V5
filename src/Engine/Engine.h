#pragma once

#include "ECS.h"
#include "Events.h"
#include "TimeStep.h"

namespace lucy {
	class Engine {
		Registry& registry = Registry::Instance();

		typedef void(*system_func)(Registry&);

		std::vector<system_func> systems_array;
		std::vector<system_func> init_systems;

	public:
		void Init();
		void Mainloop();
		void Destroy();

		void AddRuntimeSystem(system_func func);
		void AddInitializationSystem(system_func func);
	};
}