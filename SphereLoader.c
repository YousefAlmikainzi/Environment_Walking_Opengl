#include "SphereLoader.h"
#include <stdlib.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define PI 3.14159265358979323846


float *Sphere(int row, int col)
{
    int point;
    float theta;
    float phi;

    float x;
    float y;
    float z;

    int rowWidth = col + 1;

    float *sphere = malloc(sizeof(float) * row * rowWidth * FLOATPERVERTEX);

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

            sphere[point * FLOATPERVERTEX + 0] = x;
            sphere[point * FLOATPERVERTEX + 1] = y;
            sphere[point * FLOATPERVERTEX + 2] = z;

            sphere[point * FLOATPERVERTEX + 3] = x;
            sphere[point * FLOATPERVERTEX + 4] = y;
            sphere[point * FLOATPERVERTEX + 5] = z;
        }
    }
    return sphere;
}

unsigned int *Sphere_Indices(int row, int col)
{
    int a;
    int rowWidth = col + 1;
    int indexCount = col*(row - 1)*6;
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
