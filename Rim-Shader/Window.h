#pragma once

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	Window(GLint windowWidth, GLint windowHeight);

	Window() : Window(800, 600) {}

	void initialise();

	GLint getBufferWidth() { return _bufferWidth; }
	GLint getBufferHeight() { return _bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(_mainWindow); }
	GLFWwindow* getWindow() { return _mainWindow; }

	void clear(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

	void swapBuffers() { glfwSwapBuffers(_mainWindow); }

	~Window();

private:
	GLFWwindow* _mainWindow;

	GLint _width, _height;
	GLint _bufferWidth, _bufferHeight;
};