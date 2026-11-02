#include "ShaderLoader.h"
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void convertFileToString(char* strBuffer, FILE* shaderFile)
{
    fseek(shaderFile, 0, SEEK_END);
    long fileSize = ftell(shaderFile);
    rewind(shaderFile);

    fread(strBuffer, 1, fileSize, shaderFile);
    strBuffer[fileSize] = '\0';
}

unsigned int loadShader(const char* vertex, const char* fragment)
{
    FILE *vertexFile = fopen(vertex, "rb");
    FILE *fragmentFile = fopen(fragment, "rb");

    char *vertexSize = malloc(sizeof(char) * 2000);
    char *fragmentSize = malloc(sizeof(char) * 2000);

    convertFileToString(vertexSize, vertexFile);
    convertFileToString(fragmentSize, fragmentFile);
    const char* vertexString = vertexSize;
    const char* fragmentString = fragmentSize;
    fclose(vertexFile);
    fclose(fragmentFile);
    unsigned int vertexID = 0;
    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vertexString, NULL);
    glCompileShader(vertexID);

    unsigned int fragmentID = 0;
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentString, NULL);
    glCompileShader(fragmentID);

    unsigned int shaderLink = 0;
    shaderLink = glCreateProgram();
    glAttachShader(shaderLink, vertexID);
    glAttachShader(shaderLink, fragmentID);
    glLinkProgram(shaderLink);


    free(vertexSize);
    free(fragmentSize);
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    return shaderLink;
}
