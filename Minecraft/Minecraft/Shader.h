#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h";
#include "Log.h"
#include "LightSource.h"

class Shader
{
private:
    std::string VertexShaderText;
    std::string FragmentShaderText;
    GLuint ShaderProgramID;

    bool debugShader;
    glm::vec3 LightPosition;
    glm::vec3 LightColor;

    std::string ReadFile(const char* path)
    {
        std::ifstream stream(path);
        std::string file((std::istreambuf_iterator<char>(stream)),
            std::istreambuf_iterator<char>());
        return file;
    }

    void AddShader(const char* pShaderText, GLenum ShaderType)
    {
        // create a shader object
        GLuint ShaderObj = glCreateShader(ShaderType);

        if (ShaderObj == 0) {
            Log::WriteLog("Error creating shader type " + ShaderType, Error);
            exit(0);
        }
        // Bind the source code to the shader, this happens before compilation
        glShaderSource(ShaderObj, 1, (const GLchar**)&pShaderText, NULL);
        // compile the shader and check for errors
        glCompileShader(ShaderObj);
        GLint success;
        // check for shader related errors using glGetShaderiv
        glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar InfoLog[1024];
            glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
            Log::WriteLog("Error compiling shader type " + std::to_string(ShaderType) + ": " + InfoLog, Error);
            exit(1);
        }
        // Attach the compiled shader object to the program object
        glAttachShader(ShaderProgramID, ShaderObj);
    }

    GLuint CompileShaders(std::string VertexShaderText, std::string FragmentShaderText)
    {
        //Start the process of setting up our shaders by creating a program ID
        //Note: we will link all the shaders together into this ID
        ShaderProgramID = glCreateProgram();
        if (ShaderProgramID == 0) {
            Log::WriteLog("Error creating shader program.", Error);
            exit(1);
        }

        // Create two shader objects, one for the vertex, and one for the fragment shader
        AddShader(VertexShaderText.c_str(), GL_VERTEX_SHADER);
        AddShader(FragmentShaderText.c_str(), GL_FRAGMENT_SHADER);

        GLint Success = 0;
        GLchar ErrorLog[1024] = { 0 };


        // After compiling all shader objects and attaching them to the program, we can finally link it
        glLinkProgram(ShaderProgramID);
        // check for program related errors using glGetProgramiv
        glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &Success);
        if (Success == 0) {
            glGetProgramInfoLog(ShaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
            Log::WriteLog("Error linking shader program: " + std::string(ErrorLog), Error);
            exit(1);
        }

        // program has been successfully linked but needs to be validated to check whether the program can execute given the current pipeline state
        glValidateProgram(ShaderProgramID);
        // check for program related errors using glGetProgramiv
        glGetProgramiv(ShaderProgramID, GL_VALIDATE_STATUS, &Success);
        if (!Success) {
            glGetProgramInfoLog(ShaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
            Log::WriteLog("Invalid shader program: " + std::string(ErrorLog), Error);
            exit(1);
        }
        // Finally, use the linked shader program
        // Note: this program will stay in effect for all draw calls until you replace it with another or explicitly disable its use
        //glUseProgram(ShaderProgramID);
        return ShaderProgramID;
    }


public:
    Shader() {};

    Shader(const char* vertexShaderPath, const char* fragmentShaderPath, bool debug);

    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    void DebugOn();

    void DebugOff();

    GLuint GetAttribLocation(std::string shaderAttribute);

    std::string GetVertexShaderText();

    std::string GetFragmentShaderText();

    GLuint GetShaderProgramID();

    void Use();

    GLuint GetUniformLocation(const char* uniform);

    void SetUniform1f(const char* uniform, float value);

    void SetUniform1i(const char* uniform, int value);

    GLuint GetUniformMatrix4fv(const char* mat);

    void SetUniformMatrix44fv(const char* mat, glm::mat4x4* matrix);

    void SetUniformMatrix4fv(const char* mat, glm::mat4* matrix);

    GLuint GetUniformVec3(const char* vec);

    void SetUniformVec3(const char* vec, glm::vec3 vector);

    void SetUniformFloatArray(const char* name, const float arr[], int count);

    void SetLighting(LightSource* lighting);
};