#pragma once
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "Math.h"
#include "Input.h"

#include "Window.h";

#include "Log.h"


#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


namespace Engine {

    class OpenGLCallbackManager {
        static void OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
        {
            switch (severity)
            {
            case GL_DEBUG_SEVERITY_HIGH:
                LB_ERROR("[OpenGL Debug HIGH] ");
                LB_ERROR(message);
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                LB_ERROR("[OpenGL Debug MEDIUM] ");
                LB_ERROR(message);
                break;
            case GL_DEBUG_SEVERITY_LOW:
                LB_ERROR("[OpenGL Debug LOW] ");
                LB_ERROR(message);
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                LB_ERROR("[OpenGL Notification] ");
                LB_ERROR(message);
                break;
            }
        }

        static void EnableGLDebugging()
        {
            glDebugMessageCallback(OpenGLLogMessage, nullptr);
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        }
    };
}