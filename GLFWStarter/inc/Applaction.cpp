#include "Applaction.h"
#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"

Applaction::Applaction()
{
}

Applaction::~Applaction()
{
}

bool Applaction::SetUp(int windowWidh, int windowHeight)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);


	m_windowWidth = windowWidh;
	m_windowHeight = windowHeight;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "Hello World", NULL, NULL);

	if (!m_window)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		// we have successfully initialised at this point
		// so if openGL failed to load, bail out
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return false;
	}

	return true;
}

void Applaction::Run()
{
	Load();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		UpDate();
		Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	UnLoad();
}

void Applaction::shutDown()
{
	glfwTerminate();
}

void Applaction::Load()
{

}

void Applaction::UnLoad()
{
}

void Applaction::UpDate()
{
}

void Applaction::Draw()
{
}


int Applaction::GetWindowWidth() const
{
	return m_windowWidth;
}

int Applaction::GetWindowHeight() const
{
	return m_windowHeight;
}
