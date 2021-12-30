#include "Shader.h"
#include <fstream>
#include <sstream>

Engine::Shader::Shader() {}

Engine::Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {


	shaderId = glCreateProgram();

	vertexShader = Shader::compileShader(GL_VERTEX_SHADER, Shader::load(vertexShaderPath).c_str());
	fragmentShader = Shader::compileShader(GL_FRAGMENT_SHADER, Shader::load(fragmentShaderPath).c_str());


	glAttachShader(shaderId, vertexShader);
	glAttachShader(shaderId, fragmentShader);
	glLinkProgram(shaderId);
	glValidateProgram(shaderId);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Engine::Shader::Bind() {
	glUseProgram(shaderId);
}

void Engine::Shader::Unbind() {
	glUseProgram(0);
}

void Engine::Shader::setFloat(const std::string& loc, float& f) {
	GLint i = getLocation(loc);
	glUniform1f(i, f);
}

void Engine::Shader::setInt(const std::string& loc, int f) {
	GLint i = getLocation(loc);
	glUniform1i(i, f);
}

void Engine::Shader::setVector2f(const std::string& loc, Math::Vector2f& vect) {
	GLint i = getLocation(loc);
	glUniform2f(i, vect.getX(), vect.getY());
}

void Engine::Shader::setVector3f(const std::string& loc, Math::Vector3f& vect) {
	GLint i = getLocation(loc);
	glUniform3f(i, vect.getX(), vect.getY(), vect.getZ());
}


std::string Engine::Shader::load(const char* path) {
	std::ifstream t(path);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}

void Engine::Shader::Close() {
	Unbind();
	glDeleteProgram(shaderId);
}


GLuint Engine::Shader::getProgramId() {
	return shaderId;
}


int32_t Engine::Shader::getLocation(const std::string& target) {
	if (uniformsCache.find(target) != uniformsCache.end())
		return uniformsCache[target];

	GLint location = glGetUniformLocation(getProgramId(), target.c_str());

	uniformsCache[target] = location;
	return location;
}

uint32_t Engine::Shader::compileShader(int type, const char* src) {
	uint32_t id = glCreateShader(type);
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int leng;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &leng);
		char* message = (char*)alloca(leng * sizeof(char));
		glGetShaderInfoLog(id, leng, &leng, message);
		std::cout << "Error at compiling " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}


	return id;
}