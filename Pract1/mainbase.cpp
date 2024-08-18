#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 800;
GLuint VAO, VBO, shader;
float red = 0.0f, green = 0.0f, blue = 0.0f;
//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(0.0f,0.0f,0.0f,1.0f);	 			\n\
}";



void CrearTriangulo()
{
    GLfloat vertices[] = {
        //F
        -0.9f,0.6f,0.0f,
        -0.8f,0.6f,0.0f,
        -0.9f,0.0f,0.0f,

        -0.8f,0.6f,0.0f,
        -0.9f,0.0f,0.0f,
        -0.8f,0.0f,0.0f,

        -0.8f,0.6f,0.0f,
        -0.6f,0.5f,0.0f,
        -0.6f,0.6f,0.0f,

        -0.8f,0.6f,0.0f,
        -0.6f,0.5f,0.0f,
        -0.8f,0.5f,0.0f,

        -0.8f,0.4f,0.0f,
        -0.6f,0.3f,0.0f,
        -0.6f,0.4f,0.0f,

        -0.8f,0.4f,0.0f,
        -0.6f,0.3f,0.0f,
        -0.8f,0.3f,0.0f,

        //E

        -0.5f,0.5f,0.0f,
        -0.4f,0.5f,0.0f,
        -0.5f,0.0f,0.0f,

        -0.4f,0.5f,0.0f,
        -0.4f,0.0f,0.0f,
        -0.5f,0.0f,0.0f,

        -0.4f,0.5f,0.0f,
        -0.2f,0.5f,0.0f,
        -0.2f,0.4f,0.0f,

        -0.4f,0.5f,0.0f,
        -0.2f,0.4f,0.0f,
        -0.4f,0.4f,0.0f,

        -0.4f,0.3f,0.0f,
        -0.3f,0.3f,0.0f,
        -0.3f,0.2f,0.0f,

        -0.4f,0.3f,0.0f,
        -0.3f,0.2f,0.0f,
        -0.4f,0.2f,0.0f,

        -0.4f,0.1f,0.0f,
        -0.2f,0.0f,0.0f,
        -0.2f,0.1f,0.0f,

        -0.4f,0.1f,0.0f,
        -0.2f,0.0f,0.0f,
        -0.4f,0.0f,0.0f,

        //G

        -0.1f,0.6f,0.0f,
        0.05f,0.6f,0.0f,
        -0.1f,0.0f,0.0f,

        0.05f,0.6f,0.0f,
        -0.1f,0.0f,0.0f,
        0.05f,0.0f,0.0f,

        0.05f,0.6f,0.0f,
        0.25f,0.45f,0.0f,
        0.25f,0.6f,0.0f,

         0.05f,0.6f,0.0f,
        0.25f,0.45f,0.0f,
        0.05f,0.45f,0.0f,

        0.05f,0.0f,0.0f,
        0.15f,0.15f,0.0f,
        0.05f,0.15f,0.0f,

        0.05f,0.0f,0.0f,
        0.15f,0.15f,0.0f,
        0.15f,0.0f,0.0f,

        0.15f,0.0f,0.0f,
        0.25f,0.0f,0.0f,
        0.25f,0.25f,0.0f,

        0.15f,0.0f,0.0f,
        0.25f,0.25f,0.0f,
        0.15f,0.25f,0.0f,

        0.25f,0.25f,0.0f,
        0.1f,0.25f,0.0f,
        0.25f,0.35f,0.0f,

        0.25f,0.25f,0.0f,
        0.25f,0.35f,0.0f,
        0.1f,0.35f,0.0f,

        0.1f,0.35f,0.0f,
        0.25f,0.3f,0.0f,
        0.1f,0.25f,0.0f,



    };
    glGenVertexArrays(1, &VAO); //generar 1 VAO
    glBindVertexArray(VAO);//asignar VAO

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
    glEnableVertexAttribArray(0);
    //agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader


{
    GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
    const GLchar* theCode[1];
    theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);//longitud del texto
    glShaderSource(theShader, 1, theCode, codeLength);//Se le asigna al shader el código
    glCompileShader(theShader);//Se comila el shader
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    //verificaciones y prevención de errores
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("EL error al compilar el shader %d es: %s \n", shaderType, eLog);
        return;
    }
    glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
    shader = glCreateProgram(); //se crea un programa
    if (!shader)
    {
        printf("Error creando el shader");
        return;
    }
    AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
    //Para terminar de linkear el programa y ver que no tengamos errores
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
    //verificaciones y prevención de errores
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("EL error al linkear es: %s \n", eLog);
        return;
    }
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("EL error al validar es: %s \n", eLog);
        return;
    }



}
int main()
{
    // Inicialización de GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Falló inicializar GLFW\n");
        return 1;
    }

    // Configuración de GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Crear ventana
    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Clase 1", NULL, NULL);
    if (!mainWindow)
    {
        fprintf(stderr, "Falló en crearse la ventana con GLFW\n");
        glfwTerminate();
        return 1;
    }

    // Obtener tamaño de buffer
    int BufferWidth, BufferHeight;
    glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

    // Establecer contexto de OpenGL
    glfwMakeContextCurrent(mainWindow);
    glfwSwapInterval(1); // Sincronización vertical

    // Inicialización de GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Falló inicialización de GLEW\n");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Configuración de viewport
    glViewport(0, 0, BufferWidth, BufferHeight);

    // Crear triángulo y compilar shaders
    CrearTriangulo();
    CompileShaders();

    // Arreglo con los colores RGB
    float colores[][3] = { {1.0f, 0.0f, 0.0f}, // Rojo
                          {0.0f, 1.0f, 0.0f}, // Verde
                          {0.0f, 0.0f, 1.0f} }; // Azul

    int indiceColor = 0;

    // Bucle principal
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Procesar eventos
        glfwPollEvents();

        // Cambiar color
        red = colores[indiceColor][0];
        green = colores[indiceColor][1];
        blue = colores[indiceColor][2];
        indiceColor = (indiceColor + 1) % 3;

        // Limpiar pantalla
        glClearColor(red, green, blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Dibujar triángulo
        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 800);
        glBindVertexArray(0);
        glUseProgram(0);

        // Intercambiar buffers
        glfwSwapBuffers(mainWindow);

        // Esperar antes del siguiente frame
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Cambiado a 1 segundo
    }

    // Limpiar recursos
    glfwDestroyWindow(mainWindow);
    glfwTerminate();

    return 0;
}