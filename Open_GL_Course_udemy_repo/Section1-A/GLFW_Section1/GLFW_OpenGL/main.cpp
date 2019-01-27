#include <iostream>

//GLEW
#define GLEW_STATIC
#include "GL/glew.h"
//GLFW
#include "GLFW/glfw3.h"
//Shader
#include "Shader.h"
using namespace std;

///Define constants
const GLint WIDTH = 800, HEIGHT = 600;
//Define shader code


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Learning Opengl (Working title)", nullptr, nullptr);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (nullptr == window)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		cout << "Failed to initialize GLEW" << endl;

		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	///Load shader here...
	Shader myShader("core.vs", "core.frag");
	///Draw vertex
	GLfloat vertices[] = 
	{
		//position				//color
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, //Bottom Left
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,//Bottom right
		0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f //Middle-Top
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); //  bind vertex array

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //binds vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //draws the vertices

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0); //gets the pointer array
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GL_FLOAT))); //gets the pointer array
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		///Draw here...
		myShader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	///Delete resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	///Terminate program
	glfwTerminate();

	return EXIT_SUCCESS;
}