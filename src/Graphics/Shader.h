#pragma once
#ifndef GRACHICS_SHADER_H
#define GRACHICS_SHADER_H
#include <string>
#include <glm/glm.hpp>
class Shader {
public:
  unsigned int id;
  Shader(unsigned int id);
  ~Shader();

  void use();
  void uniformMatrix(const std::string& name, const glm::mat4& matrix);
};
extern Shader* load_shader(const std::string& vertexFile, const std::string& fragmentFile);
#endif // !GRACHICS_SHADER_H
