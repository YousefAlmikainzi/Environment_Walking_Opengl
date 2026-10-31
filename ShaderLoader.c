#include "ShaderLoader.h"

void convertFileToString(char* strBuffer, FILE* shaderFile)
{
    fseek(shaderFile, 0, SEEK_END);
    long fileSize = ftell(shaderFile);
    rewind(shaderFile);

    fread(strBuffer, 1, fileSize, shaderFile);
    strBuffer[fileSize] = '\0';
}
