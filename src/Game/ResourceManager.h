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

#ifndef ZYENGINE_RESOURCEMANAGER_H
#define ZYENGINE_RESOURCEMANAGER_H

#include <iostream>
#include <map>

#include <GL/glew.h>
#include "../stb_image.h"

#include "Shader.h"
#include "Texture2D.h"


class ResourceManager {
public:
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;

    static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile,
            std::string name);
    static Shader GetShader(std::string name);
    static Texture2D LoadTexture(const char *file, bool alpha, std::string name);
    static Texture2D GetTexture(std::string name);
    static void Clear();

private:
    ResourceManager() {}
    static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
    static Texture2D loadTextureFromFile(const char *file, bool alpha);
};


#endif //ZYENGINE_RESOURCEMANAGER_H
