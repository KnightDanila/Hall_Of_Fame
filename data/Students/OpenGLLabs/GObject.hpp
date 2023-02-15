#pragma once
#include <vector>


namespace Engine4AM {
	class GObject {
	private:
		const std::vector<float>* _verticies;
		unsigned int _vbo;
		unsigned int _vao;
		unsigned int _obj_dim;
		unsigned int _tex_dim;

	public:
		GObject();
		GObject(unsigned int obj_dim, unsigned int tex_dim, const std::vector<float>* verticies);
		GObject(const GObject& object);
		GObject(GObject&&) noexcept;
		virtual ~GObject();

		virtual auto get_tex_dim() const noexcept -> unsigned int;
		virtual auto get_obj_dim() const noexcept -> unsigned int;
		virtual auto get_size() const -> unsigned int;
		virtual auto select() const noexcept -> void;
	};
}
