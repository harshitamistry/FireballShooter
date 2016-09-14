#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

struct Vector2f
{
public:
	float x, y;

	Vector2f() : x(0), y(0) { }
	Vector2f(float x, float y) : x(x), y(y) { }
	Vector2f(Vector2f const &v) : x(v.x), y(v.y) { }
	Vector2f &operator=(Vector2f const &v) {
		x = v.x;
		y = v.y;
		return *this;
	}
	Vector2f &operator+=(Vector2f const &v2) {
		x += v2.x;
		y += v2.y;
		return *this;
	}
	Vector2f &operator-=(Vector2f const &v2) {
		x -= v2.x;
		y -= v2.y;
		return *this;
	}
	Vector2f &operator*=(float scale) {
		x *= scale;
		y *= scale;
		return *this;
	}
	Vector2f &operator*=(int scale) {
		x *= (float)scale;
		y *= (float)scale;
		return *this;
	}
	
	float calcMagnitude() const {
		return std::sqrt(calcMagnitudeSquared());
	}

	float calcMagnitudeSquared() const {
		return x*x + y*y;
	}

	Vector2f calcNormalizedVector() const {
		float mag = calcMagnitude();
		if (mag <= 0) {
			return Vector2f(0, 0);
		}
		return Vector2f(x / mag, y / mag);
	}

	void normalize() {
		float mag = calcMagnitude();
		x /= mag;
		y /= mag;
	}

	void rotateBy(float angle) {
		//convert the angle into randians
		float ra = angle / 180.0f * (float)M_PI;
		float rc = std::cos(ra);
		float rs = std::sin(ra);
		float newX = x * rc - y * rs;
		float newY = x * rs + y * rc;
		x = newX;
		y = newY;
	}

	float calcAngle()  const {
		return std::atan2(y, x) * 180.0f / (float)M_PI;
	}

	Vector2f operator+(Vector2f const &v2) {
		return Vector2f(x + v2.x, y + v2.y);
	}

	Vector2f operator-(Vector2f const &v2) {
		return Vector2f(x - v2.x, y - v2.y);
	}

	Vector2f operator*(float scale) {
		return Vector2f(x * scale, y * scale);
	}
	Vector2f operator*(int scale) {
		return Vector2f(x * (float)scale, y * (float)scale);
	}

	~Vector2f() { }
};

std::ostream &operator<<(std::ostream &out, Vector2f const &vector);

