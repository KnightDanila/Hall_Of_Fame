#include "GObject.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Engine4AM;

GObject::GObject() {
	_verticies = nullptr;
	_vbo = 0;
	_vao = 0;
	_obj_dim = 0;
	_tex_dim = 0;
}

GObject::GObject(unsigned int obj_dim, unsigned int tex_dim, const std::vector<float>* verticies):
	_tex_dim(tex_dim), _obj_dim(obj_dim), _verticies(verticies) {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _verticies->size() * sizeof(float), _verticies->data(), GL_STATIC_DRAW);
	auto stride = (_tex_dim + _obj_dim) * sizeof(float);
	glVertexAttribPointer(0, _obj_dim, GL_FLOAT, false, stride, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, _tex_dim, GL_FLOAT, false, stride, (void*)(_obj_dim * sizeof(float)));
	glEnableVertexAttribArray(1);
}

GObject::GObject(const GObject& object) {
	_obj_dim = object._obj_dim;
	_tex_dim = object._tex_dim;
	_verticies = object._verticies;
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _verticies->size() * sizeof(float), _verticies->data(), GL_STATIC_DRAW);
	auto stride = (_tex_dim + _obj_dim) * sizeof(float);
	glVertexAttribPointer(0, _obj_dim, GL_FLOAT, false, stride, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, _tex_dim, GL_FLOAT, false, stride, (void*)(_obj_dim * sizeof(float)));
	glEnableVertexAttribArray(1);
}

GObject::GObject(GObject&& object) noexcept {
	_obj_dim = object._obj_dim;
	_tex_dim = object._tex_dim;
	_verticies = object._verticies;
	_vao = object._vao;
	_vbo = object._vbo;
	object._verticies = nullptr;
	object._vao = 0;
	object._vbo = 0;
}

GObject::~GObject() {
	glDeleteBuffers(1, &_vbo);
}

auto GObject::get_tex_dim() const noexcept -> unsigned int {
	return _tex_dim;
}

auto GObject::get_obj_dim() const noexcept -> unsigned int {
	return _obj_dim;
}

auto GObject::get_size() const -> unsigned int
{
	return _verticies->size();
}

auto GObject::select() const noexcept -> void {
	glBindVertexArray(_vao);
}
