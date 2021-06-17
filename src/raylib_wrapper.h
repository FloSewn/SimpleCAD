#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <raylib.h>
#include <float.h>


/***********************************************************
* A wrapper for raylibs Vector2 class
***********************************************************/
class Vec2
{

public:

  Vector2 v { 0.0f, 0.0f };

  // Construct
  Vec2() {}
  Vec2(float vx, float vy) : v{vx,vy} {}
  Vec2(const Vector2& w) : v {w.x, w.y} {}

  // Copy 
  Vec2(const Vec2& w) : v{w.x, w.y} {}
  Vec2& operator=(const Vec2& w) { v.x=w.x; v.y=w.y; }

  // Move
  Vec2(Vec2&& w) : v{w.x,w.y} {}
  Vec2& operator=(Vec2&& w) { v.x=w.x; v.y=w.y; }

  // Access
  float& x = v.x;
  float& y = v.y;

  float operator[](int i) const 
  {
    if (i == 0) return v.x;
    if (i == 1) return v.y;
    else throw std::runtime_error("Invalid access to Vec2");
  }

  float& operator[](int i)  
  {
    if (i == 0) return v.x;
    if (i == 1) return v.y;
    else throw std::runtime_error("Invalid access to Vec2");
  }

  // Vector negation
  Vec2 operator-() const 
  { return Vec2{-v.x,-v.y}; }

  // Vector-Vector addition
  Vec2& operator+=(const Vec2 &w)
  { v.x += w.x; v.y += w.y; return *this; }

  // Vector-Vector subtraction
  Vec2& operator-=(const Vec2 &w)
  { v.x -= w.x; v.y -= w.y; return *this; }

  // Vector-Vector multiplication
  Vec2& operator*=(const Vec2 &w)
  { v.x *= w.x; v.y *= w.y; return *this; }

  // Vector-Vector division
  Vec2& operator/=(const Vec2 &w)
  { v.x /= w.x; v.y /= w.y; return *this; }

  // Vector-scalar addition
  template< typename T>
  Vec2& operator+=(const T s) 
  { v.x += s; v.y += s; return *this; }

  // Vector-scalar subtraction
  template< typename T>
  Vec2& operator-=(const T s) 
  { v.x -= s; v.y -= s; return *this; }

  // Vector-scalar multiplication
  template< typename T>
  Vec2& operator*=(const T s) 
  { v.x *= s; v.y *= s; return *this; }

  // Vector-scalar division
  template< typename T>
  Vec2& operator/=(const T s) 
  { v.x /= s; v.y /= s; return *this; }

  // Vector length
  float length() const
  { return std::sqrt(length_sq()); }

  // Vector length squared
  float length_sq() const
  { return v.x*v.x + v.y*v.y; }

  // Return true if each vector-value is close to zero 
  bool near_zero_values(float min=FLT_EPSILON) const
  {
    return (fabs(v.x) < min) &&
           (fabs(v.y) < min);
  }

  // Return true if vector-length is close to zero 
  bool near_zero_length(float min=FLT_EPSILON) const
  { return (length() < min); }


};

/***********************************************************
* Vec2 utility functions
***********************************************************/

// Output 
inline std::ostream& operator<<(std::ostream &out, 
                                const Vec2 &v)
{ return out << '(' << v.x << ',' << v.y << ')'; }


// Vector-Vector addition
inline Vec2 operator+(const Vec2 &u,const Vec2 &v)
{ return Vec2(u.x+v.x, u.y+v.y); }

// Vector-Vector substraction
inline Vec2 operator-(const Vec2 &u,const Vec2 &v)
{ return Vec2(u.x-v.x, u.y-v.y); }

// Vector-Vector multiplication
inline Vec2 operator*(const Vec2 &u,const Vec2 &v)
{ return Vec2(u.x*v.x, u.y*v.y); }

// Vector-Vector division
inline Vec2 operator/(const Vec2 &u,const Vec2 &v)
{ return Vec2(u.x/v.x, u.y/v.y); }


// Vector-scalar addition
template <typename T>
inline Vec2 operator+(const Vec2 &u, const T v)
{ return Vec2(u.x+v, u.y+v);}
template <typename T>
inline Vec2 operator+(const T v, const Vec2 &u)
{ return Vec2(v+u.x, v+u.y);}

// Vector-scalar substraction
template <typename T>
inline Vec2 operator-(const Vec2 &u, const T v)
{ return Vec2(u.x-v, u.y-v); }
template <typename T>
inline Vec2 operator-(const T v, const Vec2 &u)
{ return Vec2(v-u.x, v-u.y); }

// Vector-scalar multiplication
template <typename T>
inline Vec2 operator*(const Vec2 &u, const T v)
{ return Vec2(u.x*v, u.y*v); }
template <typename T>
inline Vec2 operator*(const T v, const Vec2 &u)
{ return Vec2(v*u.x, v*u.y); }

// Vector-scalar division
template <typename T>
inline Vec2 operator/(const Vec2 &u, const T v)
{ return Vec2(u.x/v, u.y/v); }
template <typename T>
inline Vec2 operator/(const T v, const Vec2 &u)
{ return Vec2(v/u.x, v/u.y); }


// Scalar product
inline float dot(const Vec2 &u, const Vec2 &v)
{ return u.x * v.x + u.y * v.y; }
// Cross product
inline float cross(const Vec2 &u, const Vec2 &v)
{ return u.x * v.y - u.y * v.x; }


// Unit-vector
inline Vec2 unit_vector(const Vec2& u)
{ return u / u.length(); }


// Equality
inline bool operator==(const Vec2& a, const Vec2& b)
{
  return (a-b).near_zero_values();
}
// Un-Equality
inline bool operator!=(const Vec2& a, const Vec2& b)
{
  return !(a==b); 
}
