#include <iostream>
#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../loaders/png_loading.h"

#include "Window.h"
#include "Events.h"
#include "Camera.h"

GLFWwindow* Window::window;
int Window::width = 0;
int Window::height = 0;



std::array<float, 30> vertices[] = {
//   x      y      z      u      v
  -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,
   1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
  -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,

   1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
   1.0f,  1.0f,  0.0f,  1.0f,  1.0f,
  -1.0f,  1.0f,  0.0f,  0.0f,  1.0f
};


int Window::initialize(int width, int height, const std::string& title) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Failed to create GLFW Window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  glViewport(0, 0, width, height);
  Window::width = width;
	Window::height = height;
  return 0;
}

void Window::setCursorMode(int mode){
	glfwSetInputMode(window, GLFW_CURSOR, mode);
}


void Window::terminate() {
  glfwTerminate();
}

bool Window::isShouldClose() {
  return glfwWindowShouldClose(window);
}

void Window::setShouldClose(bool flag) {
  glfwSetWindowShouldClose(window, flag);
}

void Window::swapBuffers() {
  glfwSwapBuffers(window);
}

void Window::run() {
  Events::initialize();

  Shader* shader = load_shader("res/main.glslv", "res/main.glslf");
  if (shader == nullptr) {
    std::cerr << "failed to load shader" << std::endl;
    Window::terminate();
    return ;
  }

  Texture* texture = load_texture("res/img.png");
  if (texture == nullptr) {
    std::cerr << "failed to load texture" << std::endl;
    delete shader;
    Window::terminate();
    return ;
  }

  // Create VAO
  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  glClearColor(0.6f, 0.62f, 0.65f, 1);


  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Camera* camera = new Camera(glm::vec3(0, 0, 1), glm::radians(40.0f));
  glm::mat4 model(1.0f);
  model = glm::translate(model, glm::vec3(0.5f,0,0));

  float lastTime = glfwGetTime();
	float delta = 0.0f;

	float camX = 0.0f;
	float camY = 0.0f;

	float speed = 5;

  while (!Window::isShouldClose()) {
    float currentTime = glfwGetTime();
		delta = currentTime - lastTime;
		lastTime = currentTime;

    if (Events::jpressed(GLFW_KEY_ESCAPE)){
			Window::setShouldClose(true);
		}
		if (Events::jpressed(GLFW_KEY_TAB)){
			Events::toogleCursor();
		}

		if (Events::pressed(GLFW_KEY_W)){
			camera->position += camera->front * delta * speed;
		}
		if (Events::pressed(GLFW_KEY_S)){
			camera->position -= camera->front * delta * speed;
		}
		if (Events::pressed(GLFW_KEY_D)){
			camera->position += camera->right * delta * speed;
		}
		if (Events::pressed(GLFW_KEY_A)){
			camera->position -= camera->right * delta * speed;
		}

		if (Events::cursor_locked){
			camY += -Events::deltaY / Window::height * 2;
			camX += -Events::deltaX / Window::height * 2;

			if (camY < -glm::radians(89.0f)){
				camY = -glm::radians(89.0f);
			}
			if (camY > glm::radians(89.0f)){
				camY = glm::radians(89.0f);
			}

			camera->rotation = glm::mat4(1.0f);
			camera->rotate(camY, camX, 0);
		}
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();
    shader->uniformMatrix("model", model);
    shader->uniformMatrix("projview", camera->getProjection()*camera->getView());
    texture->bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    glUseProgram(0);

    Window::swapBuffers();
    Events::pollEvents();
  }
  delete shader;
  delete texture;
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
}
