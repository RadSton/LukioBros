#pragma once

namespace Math {

	struct Vector2f {
		Vector2f(int x, int y);
		int getX();
		int getY();
	private:
		int m_x, m_y;
	};

}