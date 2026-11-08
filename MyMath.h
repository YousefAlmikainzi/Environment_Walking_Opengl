#ifndef MY_MATH_H
#define MY_MATH_H

typedef struct
{
    float m[16];
} mat4;

mat4 Matrix_Identity();
mat4 Matrix_Translate(float x, float y, float z);

#endif
