#include "Context.h"
#include "Animation.h"


Engine::Mesh mesh;
Engine::Shader shader;
Engine::Texture texture;
Engine::Animation animation;


void Luka::Context::Init() {
    static const GLfloat g_vertex_buffer_data[] = {
        -0.5f, -0.5f, 0.0F, 0.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f
    };

    static const GLfloat g_texutre_buffer_data[] = {
         0.0F, 0.0f,
         0.06667f, 0.0f,
         0.06667f, 0.06667f,
         0.0f, 0.06667f
    };

#if 0
    0.0F, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
#endif

    static const GLuint indecies[] = {
        0,1,2,
        2,3,0,
    };
    shader = Engine::Shader("assets/shaders/default/vertex.glsl", "assets/shaders/default/fragment.glsl");
    texture = Engine::Texture("assets/textures/tex1.png");

    mesh.Load(g_vertex_buffer_data,16, g_texutre_buffer_data, indecies,6);
    animation = Engine::Animation(&texture, 128);

    animation.addFrame(Math::Vector2f(0, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));

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
    animation.nextFrame(&mesh);
}


void Luka::Context::Render() {
    texture.Bind(0);
    shader.Bind();
    shader.setInt("u_tex", 0);
    mesh.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    mesh.Unbind();
    texture.Unbind(0);
    shader.Unbind();
}



void Luka::Context::Close() {


}
