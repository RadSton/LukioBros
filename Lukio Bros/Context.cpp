#include "Context.h"
#include "GameContent.h"

using namespace Engine;


Renderer::Basic2D renderer;
Renderer::Batch2D rendererBatch;

Luka::Intro intro;

int gamestate = 0;
/*
0: INTRO
1: MAIN MENU

*/
bool showDebugMenu = false;

void Luka::Context::Init() {
    glCullFace(GL_BACK);
    renderer.Init("assets/shaders/default/vertex.glsl", "assets/shaders/default/fragment.glsl");
    rendererBatch.Init();
    intro.Init();
}

void Luka::Context::WindowUpdate(int w, int h) {
    renderer.UpdateSize(w, h);
}

void Luka::Context::OnEvent(std::string eventname) {
    if (eventname == "finshedIntro") gamestate++;
}

void Luka::Context::Update(float deltaTime, GLFWwindow* window) {
    float speed = 500 * deltaTime;
    if (Engine::Input::isPressed(GLFW_KEY_S, window)) renderer.moveCamera(0, -speed);
    if (Engine::Input::isPressed(GLFW_KEY_W, window)) renderer.moveCamera(0, speed); // ned S weil sonst -> S - A - D
    if (Engine::Input::isPressed(GLFW_KEY_D, window)) renderer.moveCamera(speed, 0);
    if (Engine::Input::isPressed(GLFW_KEY_A, window)) renderer.moveCamera(-speed, 0);


    if (Input::isPressed(GLFW_KEY_RIGHT_CONTROL, window) && Input::isPressed(GLFW_KEY_D, window)) showDebugMenu = !Input::isPressed(GLFW_KEY_RIGHT_SHIFT, window);
    switch (gamestate) {
    case 0: intro.Update(deltaTime, window); break;
    case 1: break;
    default: Luka::MainMenu::Update(deltaTime, window); break;
    }
}


void Luka::Context::Render() {
    switch (gamestate) {
    case 0: intro.Render(&renderer, &rendererBatch); break;
    case 1: break;
    default: Luka::MainMenu::Render(&renderer, &rendererBatch); break;
    }
}


void Luka::Context::Close() {
    switch (gamestate) {
    case 0: intro.Close(); break;
    case 1: break;
    default: Luka::MainMenu::Close(); break;
    }
}

static bool wireframe = false;
static bool vsync = true;
void Luka::Context::ImGuiRender(float timings[]) {
    
    switch (gamestate) {
    case 0: intro.ImGuiRender(); break;
    case 1: break;
    default: Luka::MainMenu::ImGuiRender(); break;
    }

    if (showDebugMenu) {
        ImGui::Begin("Debug");    
        

        float engineCycle = (timings[0] + timings[1]) * 1000.0f;
        float imguiRenderTime = (engineCycle - timings[2]) * 1000.0f;
        
        ImGui::Text("DebugingTool from radston12 in Lukio Bros Engine v0.1");  
        ImGui::Text("Engine average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Render took average %.3f ms/frame (%.1f FPS)", (1000.0f * timings[0]), 1000.0f / ((1000.0f * timings[0])));
        ImGui::Text("Update took average %.3f ms/update (%.1f UPS)", (1000.0f * timings[1]), 1000.0f / ((1000.0f * timings[1])));
        ImGui::Text("Engine render cycle average %.3f ms/cycle (%.1f)", engineCycle, 1000.0f / engineCycle);
        ImGui::Text("");
        ImGui::Text("Batched Map Statistics: ");
        ImGui::Text("Squares: %i ",  rendererBatch.getStats().cubes); 
        ImGui::Text("Vertecies: %i ", rendererBatch.getStats().vertecies);

        
        ImGui::Checkbox("VSync (ON/OFF)", &vsync);
        if (vsync) glfwSwapInterval(1);
        else       glfwSwapInterval(0);
        
        ImGui::Checkbox("Wireframe Rendering Mode (ON/OFF)", &wireframe);

        if (wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         else          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



        switch (gamestate) {
        case 0: intro.ImGuiDebugRender(); break;
        case 1: Luka::MainMenu::ImGuiDebugRender(); break;
        default: Luka::MainMenu::ImGuiDebugRender(); break;
        }
        
        ImGui::End();
    }
}