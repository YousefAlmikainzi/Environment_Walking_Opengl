#include "MyMath.h"

mat4 Matrix_Identity()
{
    mat4 I = {0};

    I.m[0] = 1;
    I.m[5] = 1;
    I.m[10] = 1;
    I.m[15] = 1;
    return I;
}


mat4 Matrix_Translate(float x, float y, float z)
{
    mat4 T = Matrix_Identity();
    T.m[12] = x;
    T.m[13] = y;
    T.m[14] = z;
    return T;
}
