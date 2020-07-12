//
// Created by Narongdej Sarnsuwan on 30/6/20.
//

#include "Game.h"

GLuint Game::GameFramebuffer;
GLuint Game::GameColorBuffer;

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
    glGenFramebuffers(1, &GameFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, Game::GameFramebuffer);

    glGenTextures(1, &Game::GameColorBuffer);
    glBindTexture(GL_TEXTURE_2D, Game::GameColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Game::GameColorBuffer, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    entityManager = new EntityManager();

    // load shaders
    ResourceManager::LoadShader("../shaders/sprite.vert", "../shaders/sprite.frag", nullptr, "sprite");

    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
                                      static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    // load textures
    ResourceManager::LoadTexture("../assets/test.png", "test");

    Shader shader = ResourceManager::GetShader("sprite");
    Texture2D texture = ResourceManager::GetTexture("test");

    Entity& entity1(entityManager->AddEntity("test"));
    entity1.AddComponent<TransformComponent>(150.0f, 150.0f, 0.0f, 0.0f, 500.0f, 250.0f, 1.0f);
    entity1.AddComponent<SpriteComponent>(shader, texture, glm::vec3(1.0f, 1.0f, 1.0f));

    this->isRunning = true;
}

void Game::Update() {
    std::vector<Entity*> entities = entityManager->GetEntities();
    for(size_t i = 0; i < entities.size(); i++){
        entities[i]->Update(0);
    }
}

void Game::Render() {

    glBindFramebuffer(GL_FRAMEBUFFER, Game::GameFramebuffer);
    glViewport(0, 0, 800, 600);

    // make sure we clear the framebuffer's content
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    std::vector<Entity*> entities = entityManager->GetEntities();
    for(size_t i = 0; i < entities.size(); i++){
        entities[i]->Render();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);


}

void Game::Destroy() {
    glDeleteFramebuffers(1, &Game::GameFramebuffer);
}

std::vector<Entity *> Game::GetEntities() {
    return this->entityManager->GetEntities();
}
