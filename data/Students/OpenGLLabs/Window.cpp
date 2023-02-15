#include "Window.hpp"
#include <stdexcept>

using namespace Engine4AM;

Window::Window() {
    _width = 0;
    _height = 0;
    _title = "";
    _window = nullptr;
}

Window::Window(Window&& window) noexcept {
    _width = window._width;
    _height = window._height;
    _title = std::move(window._title);
    _window = std::move(window._window);
    window._window = nullptr;
}

Window::Window(unsigned int width, unsigned int height, const std::string& title):
    _width(width), _height(height), _title(title) {
    if (!glfwInit()) {
        throw std::runtime_error("Didn't manage to initialize GLFW.");
    }
    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
    if (!_window) {
        throw std::runtime_error("Didn't manage to create a winodw.");
    }
    glfwMakeContextCurrent(_window);
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Didn't manage to initialize GLEW.");
    }
}

Window::~Window() {
    glfwDestroyWindow(_window);
}

auto Window::get_width() const noexcept -> unsigned int {
    return _width;
}

auto Window::get_height() const noexcept -> unsigned int {
    return _height;
}

auto Window::get_title() const -> std::string {
    return _title;
}

auto Window::make_window_current() const noexcept -> void {
    glfwMakeContextCurrent(_window);
}

Window& Window::operator=(Window&& window) noexcept {
    _width = window._width;
    _height = window._height;
    _title = std::move(window._title);
    _window = std::move(window._window);
    window._window = nullptr;
    return *this;
}

Window::operator GLFWwindow* () noexcept {
    return _window;
}
