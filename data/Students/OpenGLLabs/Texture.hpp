#pragma once
#include <string>
#include <stdexcept>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

namespace Engine4AM {
	class Texture final {
	private:
		unsigned int _id;
	public:
		Texture();
		Texture(const std::string& path_to_texture);
		auto select() const -> void;
		explicit operator unsigned int() const;
	};
}
