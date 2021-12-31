#pragma once

namespace Math {

	struct Vector2f {
		Vector2f();
		Vector2f(float x, float y);
		float getX();
		float getY();
		void addX(float);
		void addY(float);
		void add(float, float);
		float m_x, m_y;
	};

}