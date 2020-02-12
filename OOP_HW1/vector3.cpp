#include <iostream>
#include <cmath>
#include "vector3.h"
using namespace std;

/* constructors */
vector3::vector3(){

}

vector3::vector3(float inX, float inY, float inZ){
    vector3::set(inX, inY, inZ);
}

vector3::vector3(const vector3 &v){
    vector3::set(v.x, v.y, v.z);
}



/* operators */
float &vector3::operator[](unsigned int index){
    if (index == 0) return x;
    else if (index == 1) return y;
    else if (index == 2) return z;
}

const float &vector3::operator[](unsigned int index) const{
    if (index == 0) return x;
    else if (index == 1) return y;
    else if (index == 2) return z;
}

vector3 &vector3::operator=(const vector3 &v){
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

vector3 &vector3::operator+=(const vector3 &v){
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vector3 &vector3::operator-=(const vector3 &v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

vector3 &vector3::operator*=(float f){
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

vector3 &vector3::operator/=(float f){
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

bool operator == (const vector3 &a, const vector3 &b){
    if (a.x != b.x) return false;
    else if (a.y != b.y) return false;
    else if (a.z != b.z) return false;
    else return true;
}

bool operator != (const vector3 &a, const vector3 &b){
    return !(a == b);
}

vector3 operator - (const vector3 &a){
    vector3 v2(-a.x, -a.y, -a.z);
    return v2;
}

vector3 operator + (const vector3 &a, const vector3 &b){
    vector3 v2(a.x + b.x, a.y + b.y, a.z + b.z);
    return v2;
}

vector3 operator - (const vector3 &a, const vector3 &b){
    vector3 v2(a.x - b.x, a.y - b.y, a.z - b.z);
    return v2;
}

vector3 operator * (float f, const vector3 &v){
    vector3 v2(v.x * f, v.y * f, v.z * f);
    return v2;
}

vector3 operator * (const vector3 &v, float f){
    vector3 v2(v.x * f, v.y * f, v.z * f);
    return v2;
}

vector3 operator / (const vector3 &v, float f){
    vector3 v2(v.x / f, v.y / f, v.z / f);
    return v2;
}



/* methods */
void vector3::set(float xIn, float yIn, float zIn){
    x = xIn;
    y = yIn;
    z = zIn;
}

float vector3::length() const{
    float square = pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2);
    return sqrt(square);
}

void vector3::printVector3() const{
    cout << '(' << x << ','
         << ' ' << y << ','
         << ' ' << z << ')' << endl;
}
