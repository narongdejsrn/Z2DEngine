//
// Created by Narongdej Sarnsuwan on 30/6/20.
//

#include "Game.h"

GLuint Game::GameFBO;
GLuint Game::GameTexture;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height) {
    this->width = width;
    this->height = height;

    // Create FBO
    glGenFramebuffers(1, &GameFBO);
    glGenTextures(1, &GameTexture);

    entityManager = new EntityManager();

    this->isRunning = true;
}

void Game::Update() {

}

void Game::Render() {
    std::vector<Entity*> entities = entityManager->GetEntities();
    for(size_t i = 0; i < entities.size(); i++){
        entities[i]->Render();
    }
}

void Game::Destroy() {

}

std::vector<Entity *> Game::GetEntities() {
    return this->entityManager->GetEntities();
}
