#ifndef MY_MATH_H
#define MY_MATH_H

typedef struct
{
    float m[16];
} mat4;

typedef struct
{
    float x, y, z;
} vec3;

mat4 Matrix_Identity();
mat4 Matrix_Translate(float x, float y, float z);
mat4 Matrix_Perspective(float FOV, float aspect, float nearZ, float farZ);
vec3 get_crossProduct(vec3 A, vec3 B);
mat4 Look_At(vec3 position, vec3 target);
float get_dotProduct(vec3 A, vec3 B);

#endif
