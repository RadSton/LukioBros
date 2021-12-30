#include "Input.h"

bool Engine::Input::isPressed(int keycode, GLFWwindow* window) {
	return glfwGetKey(window, keycode) == GLFW_PRESS;
}

bool Engine::Input::isMousePressed(int keycode, GLFWwindow* window) {
	return glfwGetMouseButton(window, keycode) == GLFW_PRESS;
}

Math::Vector2f Engine::Input::mouseLocation(GLFWwindow* window) {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	Math::Vector2f vec(xpos, ypos);
	return vec;
}
