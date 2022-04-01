//
// Created by tanguy on 31/03/22.
//

#ifndef NETWORKING_UTILS_H
#define NETWORKING_UTILS_H

#endif //NETWORKING_UTILS_H

struct vec3f{
    vec3f(){}
    vec3f(float a, float b, float c){x = a; y = b; z = c;}
    vec3f(float a, float b){x = a; y = b; z = 1.0f;}
    float x{}, y{}, z{};
};

struct vec2f{
    vec2f(){}
    vec2f(float x, float y){this->x = x; this->y = y;}
    float x{}, y{};
};

struct mat3f{
    float mat3f[3][3];
};