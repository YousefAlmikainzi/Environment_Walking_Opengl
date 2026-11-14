#include "MyMath.h"
#include <math.h>

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

//The GPU divides x, y, z by w automatically, every time, for every vertex for perspective.
//A matrix can’t divide, so it copies z into w.
//That’s identity, with the last row changed from [0 0 0 1] to [0 0 1 //0], which means m[11] = -1 and m[15] = 0.
//Result: far points get divided by a bigger number, land closer to the center, and look smaller.

//Fov is in radian
mat4 Matrix_Perspective(float FOV, float aspect, float nearZ, float farZ)
{
    float f = 1.0f / tanf(FOV * 0.5f);
    mat4 P = {0};

    P.m[0]  = f / aspect;
    P.m[5]  = f;
    P.m[10] = (farZ + nearZ) / (nearZ - farZ);
    P.m[11] = -1.0f;
    P.m[14] = (2.0f * farZ * nearZ) / (nearZ - farZ);

    return P;
}
