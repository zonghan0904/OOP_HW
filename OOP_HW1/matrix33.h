#ifndef _MATRIX33_H_
#define _MATRIX33_H_
#include "vector3.h"

class matrix33
{
public:
    /* data members */
    vector3 vec1, vec2, vec3;

public:
    /* constructors */
    matrix33();
    matrix33(const vector3 &v1, const vector3 &v2, const vector3 &v3);
    matrix33(const matrix33 &m);

public:
    /* operators */
    vector3 & operator[](unsigned int index);
    const vector3 & operator[](unsigned int index) const;

    matrix33 & operator=(const matrix33 &m);
    matrix33 & operator+=(const matrix33 &m);
    matrix33 & operator-=(const matrix33 &m);
    matrix33 & operator*=(float f);
    matrix33 & operator*=(const matrix33 &m);
    matrix33 & operator/=(float f);
    friend bool operator==(const matrix33 &a, const matrix33 &b);
    friend bool operator!=(const matrix33 &a, const matrix33 &b);
    friend matrix33 operator+(const matrix33 &a, const matrix33 &b);
    friend matrix33 operator-(const matrix33 &a);
    friend matrix33 operator-(const matrix33 &a, const matrix33 &b);
    friend matrix33 operator*(const matrix33 &a, const matrix33 &b);
    friend matrix33 operator*(const matrix33 &a, float f);
    friend matrix33 operator*(float f, const matrix33 &a);
    friend matrix33 operator/(const matrix33 &a, float f);

public:
    /* methods */
    void printMatrix();
    matrix33 invert();
    void identity();
    float determinant();
    void set_vector(vector3 &v, float x, float y, float z);
};

#endif
