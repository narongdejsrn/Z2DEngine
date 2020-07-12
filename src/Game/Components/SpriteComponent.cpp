//MIT License
//
// Copyright (c) Narongdej Sarnsuwan 2020
// narongdej.dev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "SpriteComponent.h"
#include "../Game.h"

SpriteComponent::SpriteComponent(std::string shaderName, std::string textureName, glm::vec3 color):
shaderName(shaderName), textureName(textureName), color(color){
    this->rotate = 0;
}

SpriteComponent::SpriteComponent(std::string shaderName): shaderName(shaderName), textureName("") {
    this->rotate = 0;
    this->color = {1.0f, 1.0f, 1.0f};
}

void SpriteComponent::ForceTransform(TransformComponent &transform) {
    this->transform = &transform;
}

void SpriteComponent::Initialize()
{
    if(owner != nullptr && owner->HasComponent<TransformComponent>())
        transform = owner->GetComponent<TransformComponent>();

    // configure VAO/VBO
    float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void SpriteComponent::Update(float deltaTime)
{
    if(transform == nullptr) return;
    // prepare transformations
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(transform->position, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(transform->width * transform->scale, transform->height * transform->scale
            , 1.0f));
}

void SpriteComponent::Render() {
    if(textureName.empty()) return;

    Shader shader = ResourceManager::GetShader(shaderName);
    shader.Use();
    shader.SetMatrix4("model", model);
    shader.SetVector3f("spriteColor", color);

    Texture2D texture = ResourceManager::GetTexture(textureName);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

}

SpriteComponent::~SpriteComponent() {
    glDeleteVertexArrays(1, &this->quadVAO);
    glDeleteBuffers(1, &VBO);
}

std::string SpriteComponent::GetShaderName() {
    return shaderName;
}

std::string SpriteComponent::GetTextureName() {
    return textureName;
}

void SpriteComponent::SetTexture(std::string textureName) {
    this->textureName = textureName;
}
