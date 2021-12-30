#include "Vector2f.h"

Math::Vector2f::Vector2f(int x, int y) : m_x(x), m_y(y) {}

int Math::Vector2f::getX() {
	return m_x;
}

int Math::Vector2f::getY() {
	return m_y;
}