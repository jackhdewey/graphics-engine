#include "Shader.hpp"

#include <iostream>
#include <fstream>

Shader::Shader(){}

Shader::~Shader(){
	// Deallocate Program
	glDeleteProgram(m_shaderID);
}

std::string Shader::LoadShader(const std::string& fname){

		std::ifstream myFile(fname.c_str());
        std::string line;
        std::string result;

		if (myFile.is_open()){
			while (getline(myFile,line)){
					result += line + '\n';
					// SDL_Log(line);
			}
		}
		else{
			Log("LoadShader", "File not found. Try an absolute file path to see if the file exists.");
		}
		myFile.close();
		return result;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source){

    // id is the type of shader (vertex, fragment, etc.)
    unsigned int id;

    if (type == GL_VERTEX_SHADER) {
        id = glCreateShader(GL_VERTEX_SHADER);
    } else if (type == GL_FRAGMENT_SHADER) {
        id = glCreateShader(GL_FRAGMENT_SHADER);
    }

    // The source of our shader
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);

    // Now compile our shader
    glCompileShader(id);

    // Retrieve the result of our compilation
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    // Return any compilation errors that may have occurred
    if (result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* errorMessages = new char[length]; // Could also use alloca here.
        glGetShaderInfoLog(id, length, &length, errorMessages);
        if (type == GL_VERTEX_SHADER){
            Log("CompileShader ERROR", "GL_VERTEX_SHADER compilation failed!");
            Log("CompileShader ERROR", (const char*)errorMessages);
        } else if(type == GL_FRAGMENT_SHADER){
            Log("CompileShader ERROR","GL_FRAGMENT_SHADER compilation failed!");
            Log("CompileShader ERROR",(const char*)errorMessages);
        }
        // Reclaim our memory
        delete[] errorMessages;
        // Delete our broken shader
        glDeleteShader(id);
        return 0;
    }
    return id;
}

void Shader::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource){

    // Create a new program
    unsigned int program = glCreateProgram();

    // Compile our shaders
    unsigned int myVertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Attach these shaders to our program
    glAttachShader(program, myVertexShader);
    glAttachShader(program, myFragmentShader);

    // Link and validate our program
    glLinkProgram(program);
    glValidateProgram(program);

    // Once the shaders have been linked, we can delete them.
    glDetachShader(program, myVertexShader);
    glDetachShader(program, myFragmentShader);
    glDeleteShader(myVertexShader);
    glDeleteShader(myFragmentShader);

    if(!CheckLinkStatus(program)){
        Log("CreateShader", "ERROR, shader did not link! Were there compile errors in the shader?");
    }

    m_shaderID = program;
}

bool Shader::CheckLinkStatus(GLuint programID){                                                                             
    // Retrieve the result of our compilation                                                                                           
    int result;                                                                                                                         
    // This code is returning any Linker errors that may have occurred!
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
        char* errorMessages = new char[length]; // Could also use alloca here.
        glGetProgramInfoLog(programID, length, &length, errorMessages);
        // Reclaim memory
        SDL_Log("ERROR in linking process\n");
        SDL_Log("%s\n",errorMessages);
        delete[] errorMessages;
        return false;
    }
    return true;
}

void Shader::Log(const char* system, const char* message){
    std::cout << "[" << system << "]" << message << "\n";
}

void Shader::Bind() const{
    glUseProgram(m_shaderID);
}

void Shader::Unbind() const{
    glUseProgram(0);
}

// Set a uniform 4x4 matrix in our shader.
void Shader::SetUniformMatrix4fv(const GLchar* name, const GLfloat* value){
    // search the shader for a particular variable of this name
    GLint location = glGetUniformLocation(m_shaderID, name);

    // Update the value at this uniform location
    // glUniformMatrix4v means a 4x4 matrix of floats
    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

// Set a uniform vec3 in our shader
void Shader::SetUniform3f(const GLchar* name, float v0, float v1, float v2){
    GLint location = glGetUniformLocation(m_shaderID, name);
    glUniform3f(location, v0, v1, v2);
}

// Sets a uniform integer in our shader.
void Shader::SetUniform1i(const GLchar* name, int value){
    GLint location = glGetUniformLocation(m_shaderID, name);
    glUniform1i(location, value);
}

// Sets a uniform float value in our shader
void Shader::SetUniform1f(const GLchar* name, float value){
    GLint location = glGetUniformLocation(m_shaderID, name);
    glUniform1f(location, value);
}

GLuint Shader::GetID() const{
    return m_shaderID;
}