#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

//My #include
#include "ShaderLoader.h"
#include "SphereLoader.h"

#define RESOLUTION_Y 800
#define RESOLUTION_X 800

const int row = 1000;
const int col = 1000;
const int rowWidth = col + 1;
int indexCount = col*(row - 1)*6;

typedef struct
{
    float m[16];
} mat4;

void framebuffer(GLFWwindow* window, int width, int height);
mat4 Matrix_Identity();

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

    //loadShader reads both vertex and fragment now instead of size and file
    unsigned shaderLink = loadShader("VertexShader.vs", "FragmentShader.fs");

    float *sphere = Sphere(row, col);
    unsigned int *sphereIndices = Sphere_Indices(row, col);

    unsigned VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float) * row * rowWidth * FLOATPERVERTEX, sphere,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, FLOATPERVERTEX * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, FLOATPERVERTEX * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, sphereIndices, GL_STATIC_DRAW);

    free(sphere);
    free(sphereIndices);

    int colorLoc = glGetUniformLocation(shaderLink, "uColor");
    int modelLoc = glGetUniformLocation(shaderLink, "model");
    mat4 model = Matrix_Identity();

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.3f, 0.1f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderLink);

        glBindVertexArray(VAO);
        glUniform3f(colorLoc, 0.0f, 1.0f, 1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.m);
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

mat4 Matrix_Identity()
{
    mat4 I = {0};

    I.m[0] = 1;
    I.m[5] = 1;
    I.m[10] = 1;
    I.m[15] = 1;
    return I;
}
