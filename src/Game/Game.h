//
// Created by Narongdej Sarnsuwan on 30/6/20.
//

#ifndef ZYENGINE_GAME_H
#define ZYENGINE_GAME_H

#include <vector>

#include <GL/glew.h>

#include "../Engine.h"
#include "./EntityManager.h"
#include "ResourceManager.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

class Game {

private:
    bool isRunning;
    int width, height; // Width & Height of the Game
    EntityManager* entityManager;

public:
    Game();
    ~Game();

    bool IsRunning() const;

    void Initialize(int width, int height);
    void Update();
    void Render();

    std::vector<Entity*> GetEntities();

    static GLuint GameFramebuffer;
    static GLuint GameColorBuffer;

    void Destroy();
};


#endif //ZYENGINE_GAME_H
