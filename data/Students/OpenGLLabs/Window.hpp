#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>


namespace Engine4AM {
	class Window final {
	private:
		unsigned int _width;
		unsigned int _height;
		std::string _title;
		GLFWwindow* _window;
	public:
		Window();
		Window(const Window&) = delete;
		Window(Window&& window) noexcept;
		Window(unsigned int width, unsigned int height, const std::string& title);
		~Window();
		
		auto get_width() const noexcept -> unsigned int;
		auto get_height() const noexcept -> unsigned int;
		auto get_title() const -> std::string;
		auto make_window_current() const noexcept -> void;
		
		Window& operator=(Window&& window) noexcept;
		Window& operator=(const Window&) = delete;
		operator GLFWwindow*() noexcept;
	};
}
