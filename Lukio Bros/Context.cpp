#include "Context.h"



Engine::Mesh mesh;
Engine::Texture texture;
Engine::Animation animation;

Renderer::Basic2D render;
Renderer::Batch2D renderBatch;


bool showDebugMenu = false;

void Luka::Context::Init() {

    glCullFace(GL_BACK);

    
    render.Init("assets/shaders/default/vertex.glsl", "assets/shaders/default/fragment.glsl");
    texture = Engine::Texture("assets/textures/tex1.png");

    mesh.CreateSquare(100);
    animation = Engine::Animation(&texture, 128);

    animation.addFrame(Math::Vector2f(0, 14)); 
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));
    animation.addFrame(Math::Vector2f(1, 14));


    renderBatch.Init();

    renderBatch.Begin(&texture, "assets/shaders/batch/vertex.glsl", "assets/shaders/batch/fragment.glsl");

    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            renderBatch.DrawQuad(Math::Vector2f(x*100, y*100), 80, Math::Vector2f(0, 0), 0.5f);
        }

    }
#if 0 
    renderBatch.DrawQuad(Math::Vector2f(100, 200), 100, Math::Vector2f(0, 0), 0.5f);
    renderBatch.DrawQuad(Math::Vector2f(200, 200), 100, Math::Vector2f(0, 0), 0.5f);
    renderBatch.DrawQuad(Math::Vector2f(300, 200), 100, Math::Vector2f(0, 0), 0.5f);
    renderBatch.DrawQuad(Math::Vector2f(400, 200), 100, Math::Vector2f(0, 0), 0.5f);
    renderBatch.DrawQuad(Math::Vector2f(700, 200), 100, Math::Vector2f(0, 0), 0.5f);
    renderBatch.DrawQuad(Math::Vector2f(800, 200), 100, Math::Vector2f(0, 0), 0.5f);
#endif
    renderBatch.End();
}

void Luka::Context::WindowUpdate(int w, int h) {
    render.UpdateSize(w, h);
}

void Luka::Context::Update(float deltaTime, GLFWwindow* window) {
   animation.nextFrame(&mesh);
   float speed = 500 * deltaTime;
   if (Engine::Input::isPressed(GLFW_KEY_S, window)) render.moveCamera(0,-speed );
   if (Engine::Input::isPressed(GLFW_KEY_W, window)) render.moveCamera(0, speed ); // ned S weil sonst -> S - A - D
   if (Engine::Input::isPressed(GLFW_KEY_D, window)) render.moveCamera(speed , 0);
   if (Engine::Input::isPressed(GLFW_KEY_A, window)) render.moveCamera(-speed , 0);
   if (Engine::Input::isPressed(GLFW_KEY_LEFT_CONTROL, window)) {
       if (Engine::Input::isPressed(GLFW_KEY_D, window)) {
           showDebugMenu = !Engine::Input::isPressed(GLFW_KEY_LEFT_SHIFT, window);
       }
   }
}


void Luka::Context::Render() {
    
    render.RenderMesh(&mesh, &texture);

    renderBatch.Render(&render);
}

bool vsync = true, wireframe = false;
void Luka::Context::ImGuiRender(float timings[]) {
    if (showDebugMenu) {

        ImGui::Begin("Debug");    
        

        float engineCycle = (timings[0] + timings[1]) * 1000.0f;
        float imguiRenderTime = (engineCycle - timings[2]) * 1000.0f;
        
        ImGui::Text("DebugingTool from radston12 in Lukio Bros Engine v0.1");  
        ImGui::Text("Engine average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Render took average %.3f ms/frame (%.1f FPS)", (1000.0f * timings[0]), 1000.0f / ((1000.0f * timings[0])));
        ImGui::Text("Update took average %.3f ms/update (%.1f UPS)", (1000.0f * timings[1]), 1000.0f / ((1000.0f * timings[1])));
        ImGui::Text("Engine render cycle average %.3f ms/update (%.1f)", engineCycle, 1000.0f / engineCycle);
        ImGui::Text("");
        ImGui::Text("Batched Map Statistics: ");
        ImGui::Text("Squares: %.1f ", (float) renderBatch.getStats().cubes); 
        ImGui::Text("Vertecies: %.1f ",(float) renderBatch.getStats().vertecies);

        
        ImGui::Checkbox("VSync (ON/OFF)", &vsync);
        if (vsync) {
            glfwSwapInterval(1);
        }
        else {
            glfwSwapInterval(0);
        }
        ImGui::Checkbox("Wireframe Rendering Mode (ON/OFF)", &wireframe);
        if (wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        ImGui::End();
    }
}


void Luka::Context::Close() {

    renderBatch.CleanUp();
}