//Shader cpp file//
#include "shader_compilation.h"

GLuint load_shader(const char* vertex_file_path, const char* fragment_file_path)
{
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    //Reading shaders//
    std::ifstream input_stream_vertex;
    std::string input_text_vertex;

    input_stream_vertex.open(vertex_file_path);

    if(!input_stream_vertex.is_open())
        throw std::runtime_error("Failed to open vertex shader file: " + std::string(vertex_file_path));
    else
    {
        while(input_stream_vertex.good())
        {
            std::stringstream content;
            content << input_stream_vertex.rdbuf();
            input_text_vertex = content.str();
        }
    }
    

    std::ifstream input_stream_fragment;
    std::string input_text_fragment;

    input_stream_fragment.open(fragment_file_path);

    if(!input_stream_fragment.is_open())
        throw std::runtime_error("Failed to open fragment shader file: " + std::string(fragment_file_path));
    else
    {
        while(input_stream_fragment.good())
        {
            std::stringstream content;
            content << input_stream_fragment.rdbuf();
            input_text_fragment = content.str();
        }
    }

    //Compiling shaders//
    char const* vertex_pointer = input_text_vertex.c_str();
    glShaderSource(vertex_shader_id, 1, &vertex_pointer, NULL);
    glCompileShader(vertex_shader_id);
    
    char const* fragment_pointer = input_text_fragment.c_str();
    glShaderSource(fragment_shader_id, 1, &fragment_pointer, NULL);
    glCompileShader(fragment_shader_id);

    //Error handling//
    GLint success = 0;
    GLint log_length = 0;

    if(glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success); !success)
    {
        glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &log_length);
        char* vertex_err_msg = new char[log_length + 1];
        glGetShaderInfoLog(vertex_shader_id, log_length+1, NULL, vertex_err_msg);
        glDeleteShader(vertex_shader_id);
        throw std::runtime_error("Vertex shader compilation failed: " + std::string(vertex_err_msg));
    }

    if(glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success); !success)
    {
        glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &log_length);
        char* fragment_err_msg = new char[log_length + 1];
        glGetShaderInfoLog(fragment_shader_id, log_length+1, NULL, fragment_err_msg);
        glDeleteShader(fragment_shader_id);
        throw std::runtime_error("Fragment shader compilation failed: " + std::string(fragment_err_msg));
    }

    //Setting up program//

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader_id);
    glAttachShader(program, fragment_shader_id);
    glLinkProgram(program);

    //Error handling//

    GLint link_success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &link_success);

    if(!link_success)
    {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        char* program_err_msg = new char[log_length + 1];
        glGetProgramInfoLog(program, log_length+1, NULL, program_err_msg);
        glDeleteProgram(program);
        throw std::runtime_error("Shader program linking failed: " + std::string(program_err_msg));
    }

    //Cleaning up//

    glDetachShader(program, vertex_shader_id);
    glDetachShader(program, fragment_shader_id);

    return program;
}