#include "ShaderLoader.h"
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

char* convertFileToString(FILE* shaderFile)
{
    fseek(shaderFile, 0, SEEK_END);
    long fileSize = ftell(shaderFile);
    char* shaderFileSize = malloc(sizeof(char)* (fileSize+1));
    rewind(shaderFile);

    fread(shaderFileSize, 1, fileSize, shaderFile);
    shaderFileSize[fileSize] = '\0';
    return shaderFileSize;
}

unsigned int loadShader(const char* vertex, const char* fragment)
{
    FILE *vertexFile = fopen(vertex, "rb");
    FILE *fragmentFile = fopen(fragment, "rb");

    char *vertexSize = convertFileToString(vertexFile);
    char *fragmentSize = convertFileToString(fragmentFile);

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
