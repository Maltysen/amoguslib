#pragma once

#include <constants.h>

struct vec3{
    ld x, y, z;
    vec3(ld a, ld b, ld c) : x(a), y(b), z(c) {}
    vec3() {}
};

vec3 operator+(const vec3 &a, const vec3 &b) {return {a.x+b.x, a.y+b.y, a.z+b.z};}
vec3 operator-(const vec3 &a, const vec3 &b) {return {a.x-b.x, a.y-b.y, a.z-b.z};}

vec3 operator*(const ld &f, const vec3 &a) {return {f*a.x, f*a.y, f*a.z};}
vec3 operator*(const vec3 &a, const ld &f) {return {a.x*f, a.y*f, a.z*f};}
vec3 operator/(const vec3 &a, const ld &f) {return {a.x/f, a.y/f, a.z/f};}

vec3& operator+=(vec3& a, const vec3& b) {a.x+=b.x; a.y+=b.y, a.z+=b.z; return a;}
vec3& operator-=(vec3& a, const vec3& b) {a.x-=b.x; a.y-=b.y, a.z-=b.z; return a;}
vec3& operator*=(vec3& a, const ld& f) {a.x*=f; a.y*=f, a.z*=f; return a;}
vec3& operator/=(vec3& a, const ld& f) {a.x/=f; a.y/=f, a.z/=f; return a;}

vec3 operator-(const vec3&a) {return {-a.x, -a.y, -a.z};}

// cross product
vec3 operator^(const vec3 &a, const vec3 &b) {
    return {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}

// dot product
ld operator|(const vec3 &a, const vec3&b) {return a.x*b.x + a.y*b.y + a.z*b.z;}

ld abs(const vec3 &a) {return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);}
vec3 U(const vec3 &a) {return a/abs(a);}
bool Z(const vec3 &a) {return abs(a)<EPS;}

vec3 get_perp(const vec3 &u) {
    ld v0 = abs(u.x), v1 = abs(u.y), v2 = abs(u.z);
    ll b0 = (v0 <  v1) && (v0 <  v2);
    ll b1 = (v1 <= v0) && (v1 <  v2);
    ll b2 = (v2 <= v0) && (v2 <= v1);
    return u ^ vec3((ld)b0, (ld)b1, (ld)b2);
}

// I/O
ostream& operator<<(ostream& o, vec3 v) {
    return o<<'('<<v.x<<", "<<v.y<<", "<<v.z<<')';
}

istream& operator>>(istream &o, vec3 &p) {
    ld x, y, z; o>>x>>y>>z;
    p={x, y, z};
    return o;
}
