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

#ifndef ZYENGINE_RESOURCEWINDOW_H
#define ZYENGINE_RESOURCEWINDOW_H

#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

#include "Constants.h"
#include "Game/Game.h"

class ResourceWindow {
public:
    ResourceWindow(Game& game);
    void DrawResourceWindow();

private:
    Game& game;
    void DrawSimpleImage(std::string path, ImVec2* windowSize, GLuint FBO);
    void DrawSubTree(std::string curPath);

};


#endif //ZYENGINE_RESOURCEWINDOW_H
