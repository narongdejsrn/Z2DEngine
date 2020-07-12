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
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <glm/glm.hpp>

#include "ResourceWindow.h"

std::string selectedPath;
bool imageViewerOpen;
GLuint FBO, TEX;

ResourceWindow::ResourceWindow(Game &game): game(game){
    imageViewerOpen = false;
    glGenFramebuffers(1, &FBO);
    glGenTextures(1, &TEX);
};

void DrawSubTree(std::string curPath) {
    int i = 0;
    for(const auto & entry : fs::directory_iterator(curPath)) {
        if(entry.is_directory()) {
            // Draw another subtree
            std::string nodeName = entry.path().filename().string();
            if (ImGui::TreeNode(nodeName.c_str()))
            {
                DrawSubTree(entry.path());
                ImGui::TreePop();
            }
        } else {
            ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            if (selectedPath == entry.path())
                node_flags |= ImGuiTreeNodeFlags_Selected;
            ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "%s", entry.path().filename().c_str());
            if(ImGui::IsItemClicked()) {
                selectedPath = entry.path();
                imageViewerOpen = true;
            }
            i++;
        }
    }
}

void ResourceWindow::DrawSimpleImage(std::string path, ImVec2* windowSize, GLuint FBO) {
    ResourceManager::LoadShader("../shaders/sprite.vert", "../shaders/sprite.frag", nullptr, "sprite2");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(windowSize->x),
                                      static_cast<float>(windowSize->y), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite2").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite2").SetMatrix4("projection", projection);
    Shader shader = ResourceManager::GetShader("sprite2");
    Texture2D image = ResourceManager::LoadTexture(path.c_str(), "image");

    SpriteComponent* sprite = new SpriteComponent(shader, image, glm::vec3(1.0f, 1.0f, 1.0f));
    sprite->Initialize();

    TransformComponent* transform = new TransformComponent(0.0f, 0.0f, 0.0f, 0.0f, windowSize->x, windowSize->y, 1);
    sprite->ForceTransform(*transform);
    sprite->Update(0);
    sprite->Render();
}

void ResourceWindow::DrawResourceWindow() {
    if(ImGui::Begin("File System", 0)) {
        // Read Resources folder
        std::string path = PROJECT_FOLDER + "/resources";
        DrawSubTree(path);

        ImGui::End();
    }

    if(imageViewerOpen) {
        if(ImGui::Begin("Image Viewer", &imageViewerOpen)) {
            ImVec2 windowSize = ImGui::GetWindowSize();
            ImVec2 wPos = ImGui::GetWindowPos();

            glBindFramebuffer(GL_FRAMEBUFFER, FBO);

            glBindTexture(GL_TEXTURE_2D, TEX);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowSize.x, windowSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TEX, 0);

            glBindFramebuffer(GL_FRAMEBUFFER, FBO);
            glViewport(0, 0, windowSize.x, windowSize.y);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            DrawSimpleImage(selectedPath, &windowSize, FBO);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            ImGui::GetWindowDrawList()->AddImage((void *)TEX,
                                                 { wPos.x, wPos.y},
                                                 { wPos.x + windowSize.x, wPos.y + windowSize.y},
                                                 {0, 1},
                                                 {1, 0});


            ImGui::End();
        }
    }
}