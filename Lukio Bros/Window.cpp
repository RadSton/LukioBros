#include "Window.h";



Engine::Window::Window() { Init(); }

void sizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    Luka::Context::WindowUpdate(width, height);
}


void Engine::Window::Init() {
	LB_INFO("[WINDOW] Creating Window .. ");
    if (!glfwInit()) {
        LB_ERROR("The Window could not be created! (GLFW Error)");
        Destroy();
        return;
    }


    window = glfwCreateWindow(1280, 720, "Super Luka Bros", NULL, NULL);
    if (!window)
    {
        LB_ERROR("The Window could not be created! (GLFW Create Error)");
        Destroy();
        return;
    }
    glfwMakeContextCurrent(window);
    LB_INFO("[WINDOW] Initialising OPENGL(GLEW) .. ");
    if (glewInit() != GLEW_OK) {
        LB_ERROR("OpenGL Context could not be loaded (GLEW(Modern OPENGL) Error)");
        Destroy();
        return;
    }

    LB_INFO("[ENGINE] Loading objects and textures");
    Luka::Context::Init();
    LB_INFO("[ENGINE] Done loading");

    LB_INFO("[WINDOW] Registering Windowevents");

    glfwSetWindowSizeCallback(window, sizeCallback);


    LB_INFO("[IMGUI] Init started");

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, false);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    glDepthMask(GL_FALSE);


    glfwSwapInterval(1);


    statusCode = 200;


    float lastFrameTime = (float) glfwGetTime();
    float delta = 0;
    float frameTimeNow = 0;

    float renderTime = 0, updateTime = 0, lastRender = glfwGetTime();

    LB_INFO("[WINDOW] Done initalising! ");
    while (!glfwWindowShouldClose(window))
    {

        frameTimeNow = (float) glfwGetTime();
        delta = frameTimeNow - lastFrameTime;
        lastFrameTime = frameTimeNow;


        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        lastRender = glfwGetTime();
        Luka::Context::Update(delta, window);
        updateTime = (float)glfwGetTime() - lastRender;
        lastRender = glfwGetTime();
        Luka::Context::Render();
        renderTime = (float) glfwGetTime() - lastRender;



        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        float timings[3] {renderTime,updateTime,delta};
        Luka::Context::ImGuiRender(timings);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    
}



void Engine::Window::Destroy() {
    if (statusCode == -1) {
        return;
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();


    Luka::Context::Close();
    LB_INFO("[WINDOW] Destorying  .. ");
    glfwDestroyWindow(window);
    glfwTerminate();
    statusCode = -1;
}

