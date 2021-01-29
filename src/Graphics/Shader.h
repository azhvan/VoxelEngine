#pragma once
#ifndef GRACHICS_SHADER_H
#define GRACHICS_SHADER_H
#include <string>
class Shader {
public:
  unsigned int id;
  Shader(unsigned int id);
  ~Shader();

  void use();
};

extern Shader* load_shader(std::string vertexFile, std::string fragmentFile);
#endif // !GRACHICS_SHADER_H