#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <stdio.h>

char* convertFileToString(FILE* shaderFile);
unsigned int loadShader(const char* vertex, const char* fragment);
#endif
