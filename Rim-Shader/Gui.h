#pragma once

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "Common.h"

class Gui
{
public:
	Gui() {};
	
	void initialise(GLFWwindow* window);
	void update(bool& useTexture, bool& wireFrame, bool& backFaceCull, bool& drawNormal,
		float& translation, float& scaling, float& rotation,
		float& viewPosition, float& yaw, float& pitch,
		bool& usePerspective, Material& material, Light& light, Rim& rim);
	void render();

	~Gui() {};
};

