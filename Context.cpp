#include "Context.h"


Engine::Mesh mesh;
Engine::Shader shader;
Engine::Texture texture;

void Luka::Context::Init() {
    static const GLfloat g_vertex_buffer_data[] = {
        -0.5f, -0.5f, 0.0F, 0.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f
    };

    static const GLuint indecies[] = {
        0,1,2,
        2,3,0,
    };
    shader = Engine::Shader("C:\\Users\\radston12\\Desktop\\vertex.txt", "C:\\Users\\radston12\\Desktop\\fragment.txt");
    texture = Engine::Texture("C:\\Users\\radston12\\Desktop\\luki.png");

    mesh.Load(g_vertex_buffer_data,16, indecies,6);
    
}

    
void Luka::Context::Update(float deltaTime, GLFWwindow* window) {
}

void Luka::Context::Render() {
    texture.Bind(0);
    shader.Bind();
    mesh.Bind();
    shader.setInt("u_tex", 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    mesh.Unbind();
    shader.Unbind();
    texture.Unbind(0);
}



void Luka::Context::Close() {


}
