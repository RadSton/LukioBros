#pragma once

namespace Math {

	struct Vector3f {
		Vector3f(int x, int y, int z);
		int getX();
		int getY(); 
		int getZ();
	private:
		int m_x, m_y, m_z;
	};

}