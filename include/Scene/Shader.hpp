/**
 *  @file Shader.hpp
 *  @brief Manages the loading, compiling, and linking of vertex and fragment shaders.
 *  Additionally has functions for setting various uniforms.
 */
#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include "glad/glad.h"

class Shader{
public:

    /**
     * Constructor
     */
    Shader();

    /**
     * Destructor
     */
    ~Shader();

    /**
     * Copy the contents of a shader file into a string.
     *
     * @param file_name the name of the shader file
     * @return a string containing the program code
     */
    std::string LoadShader(const std::string& file_name);

    /**
     * Creates a shader program given vertex and fragment shader source strings and updated m_programID.
     *
     * @param vertexShaderSource the string source for the vertex shader
     * @param fragmentShaderSource the string source for the fragment shader
     */
    void CreateProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

    // Bind shader program to OpenGL
    void Bind() const;

    // Unbind shader program from OpenGL
    void Unbind() const;

    // Send uniforms of different formats to the shader
    void SetUniformMatrix4fv(const GLchar* name, const GLfloat* value);
	void SetUniform3f(const GLchar* name, float v0, float v1, float v2);
    void SetUniform1i(const GLchar* name, int value);
    void SetUniform1f(const GLchar* name, float value);

    // Retrieve the shader ID
    GLuint GetID() const;

private:

    // Unique shader ID
    GLuint m_programID;

    /**
     * Compile the shader from a source string and return its id.
     *
     * @param type the shader type
     * @param source the string containing the program code
     * @return the id of the compiled shader
     */
    unsigned int CompileShader(unsigned int type, const std::string& source);

    // Makes sure shaders 'link' successfully
    bool CheckLinkStatus(GLuint programID);

    // Shader loading utility programs
    void PrintProgramLog(GLuint program);
    void PrintShaderLog(GLuint shader);

    // Logs an error message 
    void Log(const char* system, const char* message);

};

#endif
