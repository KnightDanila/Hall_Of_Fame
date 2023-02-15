#pragma once
#include <vector>
#include "Shader.hpp"
#include "Texture.hpp"
#include "GObject.hpp"

namespace Engine4AM {
	class Renderer final {
	private:
		/*unsigned int _VBO;
		unsigned int _VAO;
		unsigned int _dim;
		unsigned int _tex_dim;
		const std::vector<float>* _vertices;*/
		const GObject* _object;
		const Shader* _shader;
		const Texture* _texture;

	public:
		//Renderer(const std::vector<float>* data, unsigned int tex_dim, unsigned int dim, const Shader* shader, const Texture* texture);
		Renderer(const GObject* object, const Shader* shader, const Texture* texture);
		template<class Fn, class... Args>
		auto render(const Fn& func, Args... args) -> void;
		auto change_texture(const Texture* new_texture) -> void;
		auto change_shader(const Shader* new_shader) -> void;
		auto change_object(const GObject* new_object) -> void;
		//auto change_object(const std::vector<float>* vertices) -> void;
	};

	template<class Fn, class ...Args>
	inline auto Renderer::render(const Fn& func, Args ...args) -> void {
		glActiveTexture(GL_TEXTURE0);
		_texture->select();
		_shader->select();
		_object->select();
		func((unsigned int)(*_shader), args...);
		glDrawArrays(GL_TRIANGLES, 0, _object->get_size() / (_object->get_obj_dim() + _object->get_tex_dim()));
	}
}
