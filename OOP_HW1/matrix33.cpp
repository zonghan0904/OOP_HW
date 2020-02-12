#include <iostream>
#include <iomanip>
#include "matrix33.h"
using namespace std;

/* constructors */
matrix33::matrix33(){

}

matrix33::matrix33(const vector3 &v1, const vector3 &v2, const vector3 &v3){
    vec1 = v1;
    vec2 = v2;
    vec3 = v3;
}

matrix33::matrix33(const matrix33 &m){
    vec1 = m.vec1;
    vec2 = m.vec2;
    vec3 = m.vec3;
}



/* operators */
vector3 &matrix33::operator[](unsigned int index){
    if (index == 0) return vec1;
    else if (index == 1) return vec2;
    else if (index == 2) return vec3;
}

const vector3 &matrix33::operator[](unsigned int index) const{
    if (index == 0) return vec1;
    else if (index == 1) return vec2;
    else if (index == 2) return vec3;
}

matrix33 &matrix33::operator=(const matrix33 &m){
    vec1 = m.vec1;
    vec2 = m.vec2;
    vec3 = m.vec3;
    return *this;
}

matrix33 &matrix33::operator+=(const matrix33 &m){
    vec1 += m.vec1;
    vec2 += m.vec2;
    vec3 += m.vec3;
    return *this;
}

matrix33 &matrix33::operator-=(const matrix33 &m){
    vec1 -= m.vec1;
    vec2 -= m.vec2;
    vec3 -= m.vec3;
    return *this;
}

matrix33 &matrix33::operator*=(float f){
    vec1 *= f;
    vec2 *= f;
    vec3 *= f;
    return *this;
}

matrix33 &matrix33::operator*=(const matrix33 &m){
    vector3 v1(vec1.x*m.vec1.x+vec2.x*m.vec1.y+vec3.x*m.vec1.z,
               vec1.y*m.vec1.x+vec2.y*m.vec1.y+vec3.y*m.vec1.z,
               vec1.z*m.vec1.x+vec2.z*m.vec1.y+vec3.z*m.vec1.z);
    vector3 v2(vec1.x*m.vec2.x+vec2.x*m.vec2.y+vec3.x*m.vec2.z,
               vec1.y*m.vec2.x+vec2.y*m.vec2.y+vec3.y*m.vec2.z,
               vec1.z*m.vec2.x+vec2.z*m.vec2.y+vec3.z*m.vec2.z);
    vector3 v3(vec1.x*m.vec3.x+vec2.x*m.vec3.y+vec3.x*m.vec3.z,
               vec1.y*m.vec3.x+vec2.y*m.vec3.y+vec3.y*m.vec3.z,
               vec1.z*m.vec3.x+vec2.z*m.vec3.y+vec3.z*m.vec3.z);
    vec1 = v1;
    vec2 = v2;
    vec3 = v3;
    return *this;
}

matrix33 &matrix33::operator/=(float f){
    vec1 /= f;
    vec2 /= f;
    vec3 /= f;
    return *this;
}

bool operator==(const matrix33 &a, const matrix33 &b){
    if (a.vec1 != b.vec1) return false;
    else if (a.vec2 != b.vec2) return false;
    else if (a.vec3 != b.vec3) return false;
    else return true;
}

bool operator!=(const matrix33 &a, const matrix33 &b){
    return !(a == b);
}

matrix33 operator+(const matrix33 &a, const matrix33 &b){
    matrix33 m2(a.vec1 + b.vec1, a.vec2 + b.vec2, a.vec3 + b.vec3);
    return m2;
}

matrix33 operator-(const matrix33 &a){
    matrix33 m2(-a.vec1, -a.vec2, -a.vec3);
    return m2;
}

matrix33 operator-(const matrix33 &a, const matrix33 &b){
    matrix33 m2(a.vec1 - b.vec1, a.vec2 - b.vec2, a.vec3 - b.vec3);
    return m2;
}

matrix33 operator*(const matrix33 &a, const matrix33 &b){
    vector3 v1(a.vec1.x*b.vec1.x+a.vec2.x*b.vec1.y+a.vec3.x*b.vec1.z,
               a.vec1.y*b.vec1.x+a.vec2.y*b.vec1.y+a.vec3.y*b.vec1.z,
               a.vec1.z*b.vec1.x+a.vec2.z*b.vec1.y+a.vec3.z*b.vec1.z);
    vector3 v2(a.vec1.x*b.vec2.x+a.vec2.x*b.vec2.y+a.vec3.x*b.vec2.z,
               a.vec1.y*b.vec2.x+a.vec2.y*b.vec2.y+a.vec3.y*b.vec2.z,
               a.vec1.z*b.vec2.x+a.vec2.z*b.vec2.y+a.vec3.z*b.vec2.z);
    vector3 v3(a.vec1.x*b.vec3.x+a.vec2.x*b.vec3.y+a.vec3.x*b.vec3.z,
               a.vec1.y*b.vec3.x+a.vec2.y*b.vec3.y+a.vec3.y*b.vec3.z,
               a.vec1.z*b.vec3.x+a.vec2.z*b.vec3.y+a.vec3.z*b.vec3.z);
    matrix33 m2(v1, v2, v3);
    return m2;
}

matrix33 operator*(const matrix33 &a, float f){
    matrix33 m2(a.vec1 * f, a.vec2 * f, a.vec3 * f);
    return m2;
}

matrix33 operator*(float f, const matrix33 &a){
    matrix33 m2(a.vec1 * f, a.vec2 * f, a.vec3 * f);
    return m2;
}

matrix33 operator/(const matrix33 &a, float f){
    matrix33 m2(a.vec1 / f, a.vec2 / f, a.vec3 / f);
    return m2;
}



/* methods */
void matrix33::printMatrix(){
    cout << setw(5) << vec1[0] << setw(5) << vec2[0] << setw(5) << vec3[0] << endl
         << setw(5) << vec1[1] << setw(5) << vec2[1] << setw(5) << vec3[1] << endl
         << setw(5) << vec1[2] << setw(5) << vec2[2] << setw(5) << vec3[2] << endl;
}

matrix33 matrix33::invert(){
    float det = (*this).determinant();
    vector3 v1(vec2.y*vec3.z-vec2.z*vec3.y, vec3.y*vec1.z-vec3.z*vec1.y, vec1.y*vec2.z-vec1.z*vec2.y);
    vector3 v2(vec3.x*vec2.z-vec3.z*vec2.x, vec1.x*vec3.z-vec1.z*vec3.x, vec2.x*vec1.z-vec2.z*vec1.x);
    vector3 v3(vec2.x*vec3.y-vec2.y*vec3.x, vec3.x*vec1.y-vec3.y*vec1.x, vec1.x*vec2.y-vec1.y*vec2.x);
    matrix33 m2(v1, v2, v3);
    m2 /= det;
    return m2;
}

void matrix33::identity(){
    set_vector(vec1, 1, 0, 0);
    set_vector(vec2, 0, 1, 0);
    set_vector(vec3, 0, 0, 1);
}

float matrix33::determinant(){
    float det = 0;
    det = vec1[0]*vec2[1]*vec3[2]+vec1[1]*vec2[2]*vec3[0]
         +vec1[2]*vec2[0]*vec3[1]-vec1[2]*vec2[1]*vec3[0]
         -vec1[1]*vec2[0]*vec3[2]-vec1[0]*vec2[2]*vec3[1];
    return det;
}

void matrix33::set_vector(vector3 &v, float x, float y, float z){
    v.x = x;
    v.y = y;
    v.z = z;
}
