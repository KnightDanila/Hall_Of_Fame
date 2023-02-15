#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <ctime>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "GObject.hpp"

#define WIDTH 1000
#define HEIGHT 1000

static std::vector<float> vertices{
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

auto get_random_colored_4am_cube(int var = -1) -> const char* {
	
	unsigned int random = var == -1? rand() % 26 : (unsigned int)var;
	switch (random){
	case 0: case 1: 
		return "../OpenGLLabs/frame_yellow.jpg";
	case 2: case 3: case 4:
		return "../OpenGLLabs/frame_cian.jpg";
	case 5: case 6: case 7: case 8: 
		return "../OpenGLLabs/frame_magenta.jpg";
	case 9: case 10: case 11: case 12: case 13: case 14: case 15: 
		return "../OpenGLLabs/frame_red.jpg";
	case 16: case 17: case 18: case 19:
		return "../OpenGLLabs/frame_green.jpg";
	case 20: case 21: case 22:
		return "../OpenGLLabs/frame_blue.jpg";
	case 23: case 24:
		return "../OpenGLLabs/frame_white.jpg";
	default:
		return "../OpenGLLabs/frame_black.jpg";
	}
}

auto print_info() {
	std::cout
		<< "OpenGL lab: by Arthur Mamedov (4AM inc.)" << std::endl << std::endl
		<< "OpenGL version: " << glGetString(GL_VERSION) << std::endl << std::endl
		<< "7 cubes are rendered and drawn using shaders (vertex and fragment)." << std::endl
		<< "All these cubes are actually only one cube, rendered 7 times" << std::endl
		<< "\twith 7 different textures, but with the same shaders and vertices." << std::endl
		<< "Rotation is calculated on CPU, but size changing - on GPU." << std::endl << std::endl
		<< "To use camera, use keys 'W', 'A', 'S', 'D', SHIFT and SPACE, to close the window, press ESC or 'Q'" << std::endl;
}

auto main() -> int {
	srand(static_cast<unsigned int>(time(NULL)));
	try {
		auto window   = Engine4AM::Window(WIDTH, HEIGHT, "4am cubes");
		auto shader   = Engine4AM::Shader("../OpenGLLabs/vertex_shader.shader", "../OpenGLLabs/fragment_shader.shader");
		auto camera	  = Engine4AM::Camera(); camera.set_speed(10);
		auto texture1 = Engine4AM::Texture(get_random_colored_4am_cube(1));
		auto texture2 = Engine4AM::Texture(get_random_colored_4am_cube(3));
		auto texture3 = Engine4AM::Texture(get_random_colored_4am_cube(7));
		auto texture4 = Engine4AM::Texture(get_random_colored_4am_cube(13));
		auto texture5 = Engine4AM::Texture(get_random_colored_4am_cube(18));
		auto texture6 = Engine4AM::Texture(get_random_colored_4am_cube(21));
		auto texture7 = Engine4AM::Texture(get_random_colored_4am_cube(23));
		auto cube	  =	Engine4AM::GObject(3, 2, &vertices);
		auto renderer = Engine4AM::Renderer (&cube, &shader, &texture1);
		bool rotation = true;
		auto func = [&](unsigned int shader, glm::vec3 coords) -> void {
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);
			if (rotation)
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(66.6f), glm::vec3(0.0f, 0.1f, 0.0f));
			view = glm::translate((glm::mat4)camera, coords);
			projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
			glUniform1f(glGetUniformLocation(shader, "time"), static_cast<float>(glfwGetTime()));
			glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projection[0][0]);
		};

		float deltaTime = 0.0f;	// Time between current frame and last frame
		float lastFrame = 0.0f;
		double x = 0, y = 0;
		print_info();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPos(window, 0.0, 0.0);
		while (!glfwWindowShouldClose(window)) {
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glfwMakeContextCurrent(window);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				camera.move_forward(deltaTime);
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				camera.move_backwards(deltaTime);
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				camera.move_left(deltaTime);
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				camera.move_right(deltaTime);
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
				camera.move_up(deltaTime);
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				camera.move_down(deltaTime);
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
				break;

			float sx = static_cast<float>(x), sy = static_cast<float>(y);
			glfwGetCursorPos(window, &x, &y);

			camera.rotate(static_cast<float>(x - sx), static_cast<float>(sy - y));

			renderer.change_texture(&texture7);
			renderer.render(func, glm::vec3(7.0f, 0.0f, 0.0f));
			
			renderer.change_texture(&texture1);
			renderer.render(func, glm::vec3(4.5f, 0.0f, 5.5f));
			
			renderer.change_texture(&texture2);
			renderer.render(func, glm::vec3(-1.0f, 0.0f, 7.0f));
			
			renderer.change_texture(&texture3);
			renderer.render(func, glm::vec3(-6.5f, 0.0f, 3.0f));

			renderer.change_texture(&texture4);
			renderer.render(func, glm::vec3(-6.5f, 0.0f, -3.0f));
			
			renderer.change_texture(&texture5);
			renderer.render(func, glm::vec3(4.5f, 0.0f, -5.5f));
			
			renderer.change_texture(&texture6);
			renderer.render(func, glm::vec3(-1.0f, 0.0f, -7.0f));

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	} catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
	}
	glfwTerminate();
	return 0;
}
