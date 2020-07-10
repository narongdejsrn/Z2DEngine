//
// Created by Narongdej Sarnsuwan on 29/6/20.
//

#ifndef ZYENGINE_ENGINE_H
#define ZYENGINE_ENGINE_H

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <SDL.h>
#include <memory>


class Engine {
private:
    bool isRunning;
    static SDL_Event event;
    void DrawMainMenuBar();
    void DrawGameWindow();

public:
    Engine();
    ~Engine();
    static SDL_Renderer* renderer;
    static SDL_GLContext* gl_context;
    bool IsRunning();
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};


#endif //ZYENGINE_ENGINE_H
