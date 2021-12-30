#include "Vector2f.h"

Math::Vector2f::Vector2f(float x, float y) : m_x(x), m_y(y) {}

float Math::Vector2f::getX() {
	return m_x;
}

float Math::Vector2f::getY() {
	return m_y;
}

void Math::Vector2f::addX(float x) {
	add(x, 0);
}

void Math::Vector2f::addY(float y) {
	add(0, y);
}

void Math::Vector2f::add(float x, float y) {
	m_x += x;
	m_y += y;
}