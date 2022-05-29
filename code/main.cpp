#include "base_def.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

internal void glfw_error_callback(i32 error, const char* description);
internal u32 compile_shaders();
internal char *read_file(const char *path);

struct app_context
{
    GLFWwindow* window;
    
    u32 rendering_program;
    u32 vertex_array_object;
};
global_variable app_context app;

int 
main()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    
    // Create window with graphics context
    app.window = glfwCreateWindow(1280, 720, "AlexEngine", 0, 0);
    if (!app.window)
        return -1;
    glfwMakeContextCurrent(app.window);
    glfwSwapInterval(1); // Enable vsync
    
    // Sutup Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return -1;
    
    // Setup OpenGL
    app.rendering_program = compile_shaders();
    
    glCreateVertexArrays(1, &app.vertex_array_object);
    glBindVertexArray(app.vertex_array_object);
    
    // Main loop
    while (!glfwWindowShouldClose(app.window))
    {
        glfwPollEvents();
        
        // Rendering
        
        // Get Display
        i32 display_w, display_h;
        glfwGetFramebufferSize(app.window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(app.rendering_program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(app.window);
    }
    
    // Cleanup
    glDeleteVertexArrays(1, &app.vertex_array_object);
    glDeleteProgram(app.rendering_program);
    
    glfwDestroyWindow(app.window);
    glfwTerminate();
    
    return 0;
}

internal void 
glfw_error_callback(i32 error, const char* description)
{
    fprintf(stderr, "[GLFW] %d: %s\n", error, description);
}

internal u32 
compile_shaders()
{
    u32 vertex_shader = 0;
    u32 fragment_shader = 0;
    u32 program = 0;
    
    const char *vertex_shader_source = read_file("assets/shaders/render.vs.glsl");
    const char *fragment_shader_source = read_file("assets/shaders/render.fs.glsl");
    
    // Create and compile vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, 0);
    glCompileShader(vertex_shader);
    
    // Create and compile fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, 0);
    glCompileShader(fragment_shader);
    
    // Create program, attach shaders to it, and link it
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    // Clear
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    return program;
}

internal char 
*read_file(const char *path)
{
    FILE *file = fopen(path , "r");
    char *str = 0;
    u32 size = 0;
    if (file != 0)
    {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        str = (char*)malloc(size);
        
        fseek(file, 0, SEEK_SET);
        fread(str, 1, (size_t)size, file);
        str[size] = 0;
        
        fclose(file);
        return str;
    }
    return 0;
}


























