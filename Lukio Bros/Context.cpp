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
    shader = Engine::Shader("transformVertexShader.glsl", "transformFragmentShader.glsl");
    texture = Engine::Texture("tex0.png");

    mesh.Load(g_vertex_buffer_data,16, indecies,6);
    
}
Math::Vector2f vec(0, 0);


bool swi = false;
bool swi2 = false;
void Luka::Context::Update(float deltaTime, GLFWwindow* window) {
    if (vec.getY() < -0.5f) swi = !swi;
    if (vec.getY() > 0.5f) swi = !swi;
    if (swi) vec.addY(-0.39f * deltaTime); else vec.addY(0.39f * deltaTime);
    if (vec.getX() < -0.5f) swi2 = !swi2;
    if (vec.getX() > 0.5f) swi2 = !swi2;
    if (swi2) vec.addX(-0.4f * deltaTime); else vec.addX(0.4f * deltaTime);
}


void Luka::Context::Render() {
    texture.Bind(0);
    shader.Bind();
    mesh.Bind();
    shader.setInt("u_tex", 0);
    shader.setVector2f("pos", vec);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    texture.Unbind(0);
    mesh.Unbind();
    shader.Unbind();
}



void Luka::Context::Close() {


}
