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

vec3 get_crossProduct(vec3 A, vec3 B)
{
    vec3 r;

    r.x = (A.y * B.z) - (A.z * B.y);
    r.y = (A.z * B.x) - (A.x * B.z);
    r.z = (A.x * B.y) - (A.y * B.x);

    return r;
}

float get_dotProduct(vec3 A, vec3 B)
{
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);;
}

mat4 Look_At(vec3 position, vec3 target)
{
    mat4 camera = Matrix_Identity();

    vec3 forward;
    forward.x = position.x - target.x;
    forward.y = position.y - target.y;
    forward.z = position.z - target.z;
    float fr = sqrt(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z);
    forward.x = forward.x /fr;
    forward.y = forward.y /fr;
    forward.z = forward.z /fr;

    camera.m[2] = forward.x;
    camera.m[6] = forward.y;
    camera.m[10] = forward.z;

    vec3 defualtUp = {0, 1, 0};
    vec3 right = get_crossProduct(defualtUp, forward);
    float rr = sqrt(right.x * right.x + right.y * right.y + right.z * right.z);

    right.x = right.x / rr;
    right.y = right.y / rr;
    right.z = right.z / rr;

    camera.m[0] = right.x;
    camera.m[4] = right.y;
    camera.m[8] = right.z;

    vec3 up = get_crossProduct(forward, right);
    float ur = sqrt(up.x * up.x + up.y * up.y + up.z * up.z);
    up.x = up.x /ur;
    up.y = up.y /ur;
    up.z = up.z /ur;

    camera.m[1] = up.x;
    camera.m[5] = up.y;
    camera.m[9] = up.z;

    camera.m[12] = -get_dotProduct(right, position);
    camera.m[13] = -get_dotProduct(up, position);
    camera.m[14] = -get_dotProduct(forward, position);

    return camera;
}

