#pragma once

#include <iostream>
#include <vorbis/vorbisfile.h> 
#include <AL/al.h> 
#include <AL/alc.h>
#include <vector>
#include <string>
#include "glew.h"
#include <glm.hpp>
#include <SOIL.h>

//common function to check shader binding

bool CheckShaderCompiled(GLint shader);
//refernce to Leigh Mcloughlin for the code

void load_ogg(std::string fileName, std::vector<char> &buffer,
	ALenum &format, ALsizei &freq);

glm::vec3 getrandomwvec3(float minval, float addition);

float getrandomwfloat(float minval, float addition);

GLint TextureFromFile(const char* path, std::string directory);

GLint cubmaploader(std::string directory, std::vector<std::string> loaded_texture);

