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

#ifndef ZYENGINE_SHADER_H
#define ZYENGINE_SHADER_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    // state
    unsigned int ID;

    // constructor
    Shader() {}

    // sets the current shader as active
    Shader &Use();

    // compiles the shader from given source code
    void Compile(const char *vertexSource, const char *fragmentSource,
                 const char *geometrySource = nullptr); // note: geometry source code is optional
    // utility functions
    void SetFloat(const char *name, float value, bool useShader = false);

    void SetInteger(const char *name, int value, bool useShader = false);

    void SetVector2f(const char *name, float x, float y, bool useShader = false);

    void SetVector2f(const char *name, const glm::vec2 &value, bool useShader = false);

    void SetVector3f(const char *name, float x, float y, float z, bool useShader = false);

    void SetVector3f(const char *name, const glm::vec3 &value, bool useShader = false);

    void SetVector4f(const char *name, float x, float y, float z, float w, bool useShader = false);

    void SetVector4f(const char *name, const glm::vec4 &value, bool useShader = false);

    void SetMatrix4(const char *name, const glm::mat4 &matrix, bool useShader = false);

private:
    // checks if compilation or linking failed and if so, print the error logs
    void checkCompileErrors(unsigned int object, std::string type);
};

#endif //ZYENGINE_SHADER_H
