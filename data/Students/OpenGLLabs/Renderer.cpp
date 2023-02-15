#include "Renderer.hpp"

Engine4AM::Renderer::Renderer(const Engine4AM::GObject* object, const Shader* shader, const Texture* texture) {
	_object = object;
	_shader = shader;
	_texture = texture;
}

auto Engine4AM::Renderer::change_texture(const Texture* new_texture) -> void {
	_texture = new_texture;
}

auto Engine4AM::Renderer::change_shader(const Shader* new_shader) -> void {
	_shader = new_shader;
}

auto Engine4AM::Renderer::change_object(const GObject* new_object) -> void {
	_object = new_object;
}
