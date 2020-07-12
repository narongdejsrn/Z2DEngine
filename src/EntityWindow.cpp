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

#include "EntityWindow.h"
#include "Game/Components/TransformComponent.h"

Entity* selectedNode;

EntityWindow::EntityWindow(Game &game): game(game) {
    this->isOpen = true;
    selectedNode = nullptr;
}

unsigned int EntityWindow::GetEntitySize() {
    return 1;
}

void EntityWindow::Update() {
    DrawEntitySelection();
    DrawInspector();
}

void EntityWindow::DrawEntitySelection() {
    ImGui::Begin("Entity List", &this->isOpen);
    ImVec2 windowSize = ImGui::GetWindowSize();

    if (ImGui::Button("Create new Entity", {windowSize.x, 20})) {
        Entity& entity(game.GetEntityManager()->AddEntity("New Object"));
        entity.AddComponent<TransformComponent>(10.0f, 10.0f, 0.0f, 0.0f, 120.0f, 120.0f, 1.0f);
    }

    ImGui::Separator();

    std::vector<Entity*> entities = game.GetEntities();

    for (size_t i = 0; i < entities.size(); i++)
    {
        ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        if (selectedNode != nullptr && selectedNode == entities[i])
            node_flags |= ImGuiTreeNodeFlags_Selected;

        ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "%s", entities[i]->name);
        if (ImGui::IsItemClicked())
            selectedNode = entities[i];
    }
    ImGui::End();
}

void EntityWindow::DrawInspector() {
    if(!selectedNode) return;

    ImGui::Begin("Inspector", &this->isOpen);

    ImGui::InputText("Entity Name", selectedNode->name, IM_ARRAYSIZE(selectedNode->name));

    TransformComponent* transform = selectedNode->GetComponent<TransformComponent>();
    if(transform) {
        ImGui::Text("Transform Component");
        ImGui::DragFloat("Position X", &transform->position.x, 1);
        ImGui::DragFloat("Position Y", &transform->position.y, 1);
        ImGui::DragInt("Width", &transform->width, 1);
        ImGui::DragInt("Height", &transform->height, 1);
        ImGui::Separator();
    }

    SpriteComponent* sprite = selectedNode->GetComponent<SpriteComponent>();
    if(sprite) {
        ImGui::Text("Sprite Component");
        ImGui::Text("Shader Name: %s", sprite->GetShaderName().c_str());
        ImGui::Text("Texture Name: %s", sprite->GetTextureName().c_str());
        ImGui::SameLine();
        if(ImGui::Button("Change Texture")) {
            ImGui::OpenPopup("texture_selection");
        }
        ImGui::Separator();
    } else {
        if(ImGui::Button("Create Sprite Component")) {
            selectedNode->AddComponent<SpriteComponent>("sprite");
        }
    }

    if (ImGui::BeginPopup("texture_selection"))
    {
        for(auto& texture : ResourceManager::Textures) {
            if(ImGui::Selectable(texture.first.c_str())) {
                sprite->SetTexture(texture.first);
            }
        }
        ImGui::EndPopup();
    }
    ImGui::End();
}