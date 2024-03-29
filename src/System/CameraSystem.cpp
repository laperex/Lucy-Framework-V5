#include "CameraSystem.h"
#include <Engine/ECS.h>
#include <Engine/TimeStep.h>
#include <Engine/Window.h>
#include <Engine/Events.h>
#include <Components/Components.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <Registry/Registry.h>
#include <Engine/TimeStep.h>
#include <Engine/Events.h>
#include <Engine/Functions.h>

namespace lucy {
	void FPSView(lucy::Registry& registry, Entity entity);
	void EditorView(lucy::Registry& registry, Entity entity);
}

void lucy::System::CameraSystem(lucy::Registry& registry) {	
	static auto& timestep = registry.store<lucy::TimeStep>();
	static auto& events = registry.store<lucy::Events>();
	static std::unordered_map<Entity, glm::vec2> camera_size_map;

	auto entity = registry.store<Functions>().main_camera;

	if (entity == (Entity)0) return;
	if (!registry.contains<Camera>(entity)) return;
	if (!registry.contains<Transform>(entity)) return;

	auto& transform = registry.get<Transform>(entity);
	auto& camera = registry.get<Camera>(entity);

	if (!camera.enable) return;

	if (camera_size_map.find(entity) == camera_size_map.end())
		camera_size_map[entity] = { 0, 0 };

	auto& last_size = camera_size_map[entity];

	if (camera.width != last_size.x || camera.height != last_size.y) {
		camera_size_map[entity] = { camera.width, camera.height };

		camera.lastx = camera.width / 2;
		camera.lasty = camera.height / 2;

		camera.first_mouse = true;

		float aspect = (float) camera.width / camera.height;

		if (camera.type == PERSPECTIVE) {
			camera.projection = glm::perspective(glm::radians(camera.fov), aspect, camera.c_near, camera.c_far);
		} else if (camera.type == ORTHOGRAPHIC) {
			camera.projection = glm::ortho<float>(-camera.width, camera.width, -camera.height, camera.height, -camera.c_near, camera.c_far);
		}
	}

	switch (camera.mode) {
		case ViewMode_FPS:
			FPSView(registry, entity);
			break;

		case ViewMode_Editor:
			EditorView(registry, entity);
			break;

		default:
			const auto& quaternion = transform.GetRotationQuat();

			camera.front = glm::normalize(quaternion * camera.world_front);
			camera.up = glm::normalize(quaternion * camera.world_up);

			camera.view = glm::lookAt(transform.translation, transform.translation + camera.front, camera.up) + transform.GetScaleMatrix();
			camera.position = transform.translation;
	}
}

void lucy::FPSView(lucy::Registry& registry, Entity entity) {	
	static auto& timestep = registry.store<lucy::TimeStep>();
	static auto& events = registry.store<lucy::Events>();

	auto& transform = registry.get<Transform>(entity);
	auto& camera = registry.get<Camera>(entity);

	if (events.IsButtonPressed(SDL_BUTTON_MIDDLE)) {
		auto pos = events.GetCursorPos();

		if (camera.first_mouse) {
			camera.lastx = pos.x;
			camera.lasty = pos.y;
			camera.first_mouse = false;
		}

		transform.rotation.y -= (pos.x - camera.lastx) * camera.sensitivity;
		transform.rotation.x += (camera.lasty - pos.y) * camera.sensitivity;

		camera.lastx = pos.x;
		camera.lasty = pos.y;
	} else {
		camera.first_mouse = true;
	}

	const auto& quaternion = transform.GetRotationQuat();

	camera.front = glm::normalize(quaternion * camera.world_front);
	camera.up = glm::normalize(quaternion * camera.world_up);

	const auto& dt = timestep.GetTimeStep();
	const float speed = 0.5 * dt;

	if (events.IsKeyPressed(SDL_SCANCODE_W))
		transform.translation += camera.front * speed;
	if (events.IsKeyPressed(SDL_SCANCODE_S))
		transform.translation -= camera.front * speed;
	if (events.IsKeyPressed(SDL_SCANCODE_A))
		transform.translation -= glm::normalize(glm::cross(camera.front, camera.up)) * speed;
	if (events.IsKeyPressed(SDL_SCANCODE_D))
		transform.translation += glm::normalize(glm::cross(camera.front, camera.up)) * speed;
	if (events.IsKeyPressed(SDL_SCANCODE_LALT))
		transform.translation -= camera.up * speed;
	if (events.IsKeyPressed(SDL_SCANCODE_SPACE))
		transform.translation += camera.up * speed;

	camera.view = glm::lookAt(transform.translation, transform.translation + camera.front, camera.up);
	camera.position = transform.translation;
}

void lucy::EditorView(lucy::Registry& registry, Entity entity) {
	
}
