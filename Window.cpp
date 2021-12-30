#include "Window.h";



Engine::Window::Window() { Init(); }

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
    //https://youtu.be/n4k7ANAFsIQ?t=1039
    glfwMakeContextCurrent(window);
    LB_INFO("[WINDOW] Initialising OPENGL(GLEW) .. ");
    if (glewInit() != GLEW_OK) {
        LB_ERROR("OpenGL Context could not be loaded (GLEW(Modern OPENGL) Error)");
        Destroy();
        return;
    }


    Luka::Context::Init();

    glfwSwapInterval(1);


    statusCode = 200;


    float lastFrameTime = (float) glfwGetTime();
    float delta = 0;
    float frameTimeNow = 0;

    LB_INFO("[WINDOW] Done initalising! ");
    while (!glfwWindowShouldClose(window))
    {

        frameTimeNow = (float) glfwGetTime();
        delta = frameTimeNow - lastFrameTime;
        lastFrameTime = frameTimeNow;


        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        Luka::Context::Update(delta, window);
        Luka::Context::Render();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    
}

void Engine::Window::Destroy() {
    if (statusCode == -1) {
        return;
    }
    Luka::Context::Close();
    LB_INFO("[WINDOW] Destorying  .. ");
    glfwTerminate();
    statusCode = -1;
}



