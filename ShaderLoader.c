#include "ShaderLoader.h"
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

char* convertFileToString(FILE* shaderFile)
{
    fseek(shaderFile, 0, SEEK_END);
    long fileSize = ftell(shaderFile);
    char* shaderSource = malloc(sizeof(char)* (fileSize+1));
    rewind(shaderFile);

    fread(shaderSource, 1, fileSize, shaderFile);
    shaderSource[fileSize] = '\0';
    return shaderSource;
}

unsigned int loadShader(const char* vertex, const char* fragment)
{
    FILE *vertexFile = fopen(vertex, "rb");
    FILE *fragmentFile = fopen(fragment, "rb");

    char *vertexSource = convertFileToString(vertexFile);
    char *fragmentSource = convertFileToString(fragmentFile);

    const char* vertexString = vertexSource;
    const char* fragmentString = fragmentSource;
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


    free(vertexSource);
    free(fragmentSource);
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    return shaderLink;
}
