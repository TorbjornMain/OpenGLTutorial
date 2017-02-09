// OpenGLTutorial.cpp : Defines the entry point for the console application.
//

#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <aie\Gizmos.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

int main()
{
	if (glfwInit() == false)
		return -1;
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Shazbot", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);
	
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	std::cout << "GL Version: " << major << "." << minor << std::endl;

	Gizmos::create();
	
	mat4 view = glm::lookAt(vec3(10 * glm::cos(0), 10, 10 * glm::sin(0)), vec3(0), vec3(0, 1, 0));
	mat4 proj = glm::perspective(glm::pi<float>() * 0.3f, 16 / 9.0f, 0.1f, 1000.0f);

	float x = 0.0f;

	while ((glfwWindowShouldClose(window) == false) && (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS))
	{
		x += 0.01f;
		//Clear
		glClearColor(0, 0, 0, 1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Gizmos::clear();

		
		//Main Update
		Gizmos::addTransform(glm::mat4(1));
		vec4 white(1, 0, 0, 1);
		vec4 black(0, 0, 1, 1);



		for (int i = 0; i < 21; i++)
		{
			Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), white * (1 - (i / 20.f)) + black * (i / 20.0f));
			Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), white * (1 - (i / 20.f)) + black * (i / 20.0f));

		}

		view = glm::lookAt(vec3(10*glm::cos(x), 10, 10*glm::sin(x)), vec3(0), vec3(0, 1, 0));

		Gizmos::draw(proj * view);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Close program
	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

