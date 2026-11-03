#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//My #include
#include "ShaderLoader.h"

#define RESOLUTION_Y 800
#define RESOLUTION_X 800
#define PI 3.14159265358979323846

const int row = 1000;
const int col = 1000;
const int rowWidth = col + 1;
int FloatPerVer = 6;
int indexCount = col*(row - 1)*6;

void framebuffer(GLFWwindow* window, int width, int height);
float *Sphere();
unsigned int *Sphere_Indices();

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(RESOLUTION_X, RESOLUTION_Y, "Environment_Scene", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((void*)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glfwSetFramebufferSizeCallback(window, framebuffer);

    //reading shader files, creating malloc for the, converting them into strings
    unsigned shaderLink = loadShader("VertexShader.vs", "FragmentShader.fs");

    float *sphere = Sphere();
    unsigned int *sphereIndices = Sphere_Indices();

    unsigned VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float) * row * rowWidth * FloatPerVer, sphere,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, FloatPerVer * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, FloatPerVer * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, sphereIndices, GL_STATIC_DRAW);

    free(sphere);
    free(sphereIndices);

    int colorLoc = glGetUniformLocation(shaderLink, "uColor");

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.3f, 0.1f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderLink);

        glBindVertexArray(VAO);
        glUniform3f(colorLoc, 0.0f, 1.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

void framebuffer(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width, height);
}

float *Sphere()
{
    int point;
    float theta;
    float phi;

    float x;
    float y;
    float z;

    float *sphere = malloc(sizeof(float) * row * rowWidth * FloatPerVer);

    for(int i = 0; i < row; i++)
    {
        theta = i * PI / (float)(row - 1);
        for(int j = 0; j < rowWidth; j++)
        {
            point = i * rowWidth + j;
            phi = j * 2*PI / col;
            x = sin(theta) * cos (phi);
            y = cos(theta);
            z = sin(theta) * sin(phi);

            sphere[point * FloatPerVer + 0] = x;
            sphere[point * FloatPerVer + 1] = y;
            sphere[point * FloatPerVer + 2] = z;

            sphere[point * FloatPerVer + 3] = x;
            sphere[point * FloatPerVer + 4] = y;
            sphere[point * FloatPerVer + 5] = z;
        }
    }
    return sphere;
}

unsigned int *Sphere_Indices()
{
    int a;
    unsigned int *sphereIndices = malloc(sizeof(unsigned int) * indexCount);
    int counter = 0;

    for(int i = 0; i < row - 1; i++)
    {
        for (int j = 0; j < col; j++)

        {
            a = i * rowWidth + j;
            sphereIndices[counter] = a;
            counter++;
            sphereIndices[counter] = a + 1;
            counter++;
            sphereIndices[counter] = a + rowWidth;
            counter++;
            sphereIndices[counter] = a + 1;
            counter++;
            sphereIndices[counter] = a + rowWidth + 1;
            counter++;
            sphereIndices[counter] = a + rowWidth;
            counter++;
        }
    }

    return sphereIndices;
}
