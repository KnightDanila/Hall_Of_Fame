#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace Engine4AM {
	class Camera final {
	private:
		float _speed = 1.0f;
		float _sensitivity = 0.1f;
		float _yaw = 0.0f;
		float _pitch = 0.0f;
		glm::vec3 _pos;
		glm::vec3 _front;
		glm::vec3 _up;
	public:
		Camera();
		Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up);
		auto set_speed(size_t speed) -> void;
		auto move_forward(float delta = 1.0f) -> void;
		auto move_backwards(float delta = 1.0f) -> void;
		auto move_right(float delta = 1.0f) -> void;
		auto move_left(float delta = 1.0f) -> void;
		auto move_up(float delta = 1.0f) -> void;
		auto move_down(float delta = 1.0f) -> void;
		auto rotate(float x_rad, float y_rad) -> void;
		operator glm::mat4();
	};
}
