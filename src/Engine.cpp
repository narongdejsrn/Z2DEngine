//
// Created by Narongdej Sarnsuwan on 29/6/20.
//

#include "Engine.h"
#include "Game.h"

SDL_Window* window;
ImGuiIO* io;
SDL_Event Engine::event;
SDL_GLContext* Engine::gl_context;
SDL_Renderer* Engine::renderer;
Game* game;

Engine::Engine() {
    this->isRunning = true;
}

void Engine::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return;
    }

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    window = SDL_CreateWindow("ZYEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, window_flags);
    renderer = SDL_CreateRenderer(window, -1, 0);
    gl_context = static_cast<SDL_GLContext *>(SDL_GL_CreateContext(window));

    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    glewExperimental = GL_TRUE;

    bool err = glewInit() != GLEW_OK;
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    }

    // SETUP Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Initialize Game Window
    game = new Game();
    game->Initialize();

    this->isRunning = true;
}

/* Process the input into the engine */
void Engine::ProcessInput() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: {
            this->isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if(event.key.keysym.sym == SDLK_ESCAPE) {
                this->isRunning = false;
            }
            break;
        }
        case SDL_WINDOWEVENT: {
            if(event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)) {
                this->isRunning = false;
            }
            break;
        }
        default : {
            break;
        }
    }
}

void Engine::DrawMainMenuBar() {
    bool mainMenuOpen;
    if(ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Hi")) {
            ImGui::MenuItem("Metrics", NULL, &mainMenuOpen);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Engine::DrawGameWindow() {
    if(ImGui::Begin("Game")) {
        game->Render();
        ImGui::Image((void *)game->GetTextureID(), ImGui::GetWindowSize(),
                ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }
}

void Engine::Update() {
    // Start a new IMGui Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    DrawMainMenuBar();
    DrawGameWindow();
}

void Engine::Render() {
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui::Render();

    glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window);
}

bool Engine::IsRunning() {
    return this->isRunning;
}

void Engine::Destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}