//
// Created by Narongdej Sarnsuwan on 29/6/20.
//

#ifndef ZYENGINE_ENGINE_H
#define ZYENGINE_ENGINE_H

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <SDL.h>
#include <GL/gl3w.h>
#include <memory>


class Engine {
private:
    bool isRunning;
    static SDL_Event event;

public:
    Engine();
    ~Engine();
    bool IsRunning();
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};


#endif //ZYENGINE_ENGINE_H
