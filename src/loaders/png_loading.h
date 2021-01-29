#pragma once
#ifndef LOADERS_PNG_LOADING_H
#define LOADERS_PNG_LOADING_H

#include <string>
#include "../Graphics/Texture.h"

class Texture;
extern Texture* load_texture(std::string fileName);

#endif // !LOADERS_PNG_LOADING_H