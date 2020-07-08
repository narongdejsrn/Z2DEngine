//
// Created by Narongdej Sarnsuwan on 30/6/20.
//

#ifndef ZYENGINE_GAME_H
#define ZYENGINE_GAME_H

#include <glew.h>

#include "Engine.h"

class Game {
public:
    void Initialize();
    void Update();
    void Render();

    GLuint GetTextureID();
};


#endif //ZYENGINE_GAME_H
