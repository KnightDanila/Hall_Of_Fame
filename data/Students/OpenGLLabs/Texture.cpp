#include "Texture.hpp"

using namespace Engine4AM;

Texture::Texture() :_id(0) {
	;
}

Texture::Texture(const std::string& path_to_texture) {
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channels;

	unsigned char* data = stbi_load(path_to_texture.c_str(), &width, &height, &channels, 0);
	if (!data) {
		stbi_image_free(data);
		throw std::runtime_error("Didn't manage to lead texture.");
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

auto Texture::select() const -> void {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _id);
}

Texture::operator unsigned int() const {
	return _id;
}
