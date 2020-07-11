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
    DrawEntityDetail();
}

void EntityWindow::DrawEntitySelection() {
    ImGui::Begin("Entity List", &this->isOpen);

    std::vector<Entity*> entities = game.GetEntities();

    if(selectedNode != nullptr)
        ImGui::Text("Selected: %s", selectedNode->name.c_str());

    if (ImGui::TreeNode("Entities"))
    {
        for (size_t i = 0; i < entities.size(); i++)
        {
            ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            if (selectedNode != nullptr && selectedNode == entities[i])
                node_flags |= ImGuiTreeNodeFlags_Selected;

            ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "%s", entities[i]->name.c_str());
            if (ImGui::IsItemClicked())
                selectedNode = entities[i];
        }

        ImGui::TreePop();
    }
    ImGui::End();
}

void EntityWindow::DrawEntityDetail() {
    if(!selectedNode) return;

    ImGui::Begin("Entity Detail", &this->isOpen);

    TransformComponent* transform = selectedNode->GetComponent<TransformComponent>();
    ImGui::DragFloat("Position X", &transform->position.x, 1);
    ImGui::DragFloat("Position Y", &transform->position.y, 1);
    ImGui::DragInt("Width", &transform->width, 1);
    ImGui::DragInt("Height", &transform->height, 1);
    ImGui::End();
}