#include "Camera.hpp"

using namespace Engine4AM;

Camera::Camera() {
	_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up) :
	_pos(pos), _front(front), _up(up) {
	;
}

auto Camera::set_speed(size_t speed) -> void {
	_speed = speed;
}

auto Camera::move_forward(float delta) -> void {
	_pos += _speed * delta * _front;
}

auto Camera::move_backwards(float delta) -> void {
	_pos -= _speed * delta * _front;
}

auto Camera::move_right(float delta) -> void {
	_pos += glm::normalize(glm::cross(_front, _up)) * _speed * delta;
}

auto Camera::move_left(float delta) -> void {
	_pos -= glm::normalize(glm::cross(_front, _up)) * _speed * delta;
}

auto Camera::move_up(float delta) -> void {
	_pos[1] += _speed * delta;
}

auto Camera::move_down(float delta) -> void {
	_pos[1] -= _speed * delta;
}

auto Camera::rotate(float x_rad, float y_rad) -> void {
	_yaw += x_rad * _sensitivity;
	_pitch += y_rad * _sensitivity;
	glm::vec3 direction;
	direction.x = glm::cos(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));
	direction.y = glm::sin(glm::radians(_pitch));
	direction.z = glm::sin(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));
	_front = glm::normalize(direction);
}

Camera::operator glm::mat4() {
	return glm::lookAt(_pos, _pos + _front, _up);
}