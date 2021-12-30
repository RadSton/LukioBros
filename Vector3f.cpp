#include "Vector3f.h"

Math::Vector3f::Vector3f(int x, int y, int z) : m_x(x), m_y(y), m_z(z) {}

int Math::Vector3f::getX() {
	return m_x;
}

int Math::Vector3f::getY() {
	return m_y;
}

int Math::Vector3f::getZ() {
	return m_z;
}