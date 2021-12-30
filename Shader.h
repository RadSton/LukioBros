#pragma once
#include "Core.h"
#include <string>
#include <unordered_map> 

namespace Engine {
	class Shader {
	public:
		Shader();
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		  GLuint getProgramId();
		  void Bind();
		  void Unbind();

		  void setFloat(const std::string& loc, float& f);
		  void setInt(const std::string& loc, int f);
		  void setVector2f(const std::string& loc, Math::Vector2f& vect);
		  void setVector3f(const std::string& loc, Math::Vector3f& vect);


		  void Close();
	private:
		std::string load(const char*);

		std::unordered_map<std::string, GLint> uniformsCache;
		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint shaderId;
		uint32_t compileShader(int type, const char* src);
		int32_t getLocation(const std::string& target);
	};
}