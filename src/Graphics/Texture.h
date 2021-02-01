#pragma once
#ifndef GRACHICS_TEXTURE_H
#define GRACHICS_TEXTURE_H

class string;
class Texture{
public:
  unsigned int id;
  int width;
  int height;
  Texture(unsigned int id, int width, int height);
  ~Texture();
  void bind();
};
extern Texture* load_texture(const std::string& filename);
#endif // !GRACHICS_TEXTURE_H
