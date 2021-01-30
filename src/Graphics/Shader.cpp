#include "Shader.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(unsigned int id) : id(id) {}

Shader::~Shader() {
  glDeleteProgram(id);
}

void Shader::use() {
  glUseProgram(id);
}

void Shader::uniformMatrix(std::string name, glm::mat4 matrix){
  GLuint transformLoc = glGetUniformLocation(id, name.c_str());
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader* load_shader(std::string vertexFile, std::string fragmentFile) {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::badbit);
  try {
    vShaderFile.open(vertexFile);
    fShaderFile.open(fragmentFile);
    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (std::ifstream::failure& e) {
    std::cerr << "ERROR::SHADER::FILE_NOT SUCCESFULLY_READ" << std::endl;
    return nullptr;
  }
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, nullptr);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
    std::cerr << "SHADER::VERTEX: compilation failed\n" << infoLog << std::endl;
    return nullptr;
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, nullptr);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
    std::cerr << "SHADER::FRAGMENT: compilation failed\n" << infoLog << std::endl;
    return nullptr;
  }

  int id = glCreateProgram();
  glAttachShader(id, vertex);
  glAttachShader(id, fragment);
  glLinkProgram(id);

  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, nullptr, infoLog);
    std::cerr << "SHADER::PROGRAM: linking failed\n" << infoLog << std::endl;

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return nullptr;
  }
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return new Shader(id);
}
