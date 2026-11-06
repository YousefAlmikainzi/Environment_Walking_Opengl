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
