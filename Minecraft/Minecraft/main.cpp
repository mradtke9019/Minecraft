#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "Sky.h"
#include "Block.h"
#include "ICamera.h"
#include "FixedCamera.h"
#include "LightSource.h"
#include "FirstPersonCamera.h"
#include "Utility.h"
#include "Chunk.h"
#include "RayIntersectionHelper.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

int Width;
int Height;
using namespace std;

std::vector<Chunk*> chunks;
Chunk* chunk;
Block* b;
Model* blocKModel;
Shader* activeShader;
//ICamera* activeCamera;
FirstPersonCamera* activeCamera = new FirstPersonCamera(glm::vec3(0.0f, 0.0f, -5.0f));
LightSource* lighting;
Utility* bookKeeper;
bool firstMouse = true;
float lastX; //= SCR_WIDTH / 2.0f;
float lastY;// = SCR_HEIGHT / 2.0f;
std::map<int,bool> keymap;

glm::mat4 GetProjection()
{
	return glm::perspective(glm::radians(60.0f), (float)Width / (float)Height, 0.1f, 300.0f);
}


void SetBackgroundColor(float time)
{
	float dayDuration = 10.0f;
	glm::vec4 backgroundcolor = glm::vec4(Sky::GetColorForTimeOfDay(time, dayDuration), 1.0f);
	glClearColor(backgroundcolor.r, backgroundcolor.g, backgroundcolor.b, 1.0f);
}


void display(GLFWwindow* window)
{
	float currentTime = glfwGetTime();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetBackgroundColor(currentTime);

	glm::mat4 projection = GetProjection();

	activeShader->SetLighting(lighting);
	//activeShader->SetUniform1f("time", timeValue);
	//activeShader->SetUniform1f("rand", r);
	activeShader->SetUniformMatrix4fv("view", activeCamera->GetViewTransform());
	activeShader->SetUniformMatrix4fv("projection", &projection);
	activeShader->SetUniformVec3("cameraPos", activeCamera->GetPosition());

	for (auto c : chunks)
	{
		c->Draw();
	}

}

void LoadShaders()
{
	activeShader = new Shader("./blinnPhong.vert", "./blinnPhong.frag");
}


void LoadCameras()
{
	glm::vec3 position = glm::vec3(-30, 30, 30);
	glm::vec3 target = glm::vec3(0, 0, 0);
	glm::vec3 up = glm::vec3(0, 1, 0);
	//activeCamera = new FixedCamera(position, target, up);

	//activeCamera = new FirstPersonCamera(glm::vec3(0.0f, 0.0f, -2.0f));
}

void LoadObjects()
{
	blocKModel = new Model("./unit_cube.obj", activeShader);
	b = new Block(blocKModel);

	chunk = new Chunk(glm::vec3(0,0,0), *b);

	chunks = std::vector<Chunk*>();
	chunks.push_back(chunk);
	chunks.push_back(new Chunk(glm::vec3(1, 0, 0), *b));
	chunks.push_back(new Chunk(glm::vec3(2, 0, 0), *b));
}

void initLight()
{
	lighting = new LightSource(glm::vec3(10, 10, 10), glm::vec3(1, 1, 1));
}

void initUtility() 
{
	bookKeeper = new Utility(); 
}


void init()
{
	glEnable(GL_DEPTH_TEST);
	glm::vec4 backgroundcolor = glm::vec4(Sky::GetColorForTimeOfDay(75, 600), 1.0f);;
	glClearColor(backgroundcolor.r, backgroundcolor.g, backgroundcolor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	initLight();
	initUtility();
	LoadShaders();
	LoadCameras();
	LoadObjects();
}

void processInput()
{
	for (auto key : keymap)
	{
		int KEY = key.first;
		bool pressed = key.second;
		switch (KEY)
		{
		case GLFW_KEY_W:
			if (pressed)
			{
				activeCamera->HandleKeyboardInput(FirstPersonCamera::FWD, bookKeeper->GetDeltaTime());
			}
			break;
		case GLFW_KEY_S:
			if (pressed)
			{
				activeCamera->HandleKeyboardInput(FirstPersonCamera::BACK, bookKeeper->GetDeltaTime());
			}
			break;
		case GLFW_KEY_A:
			if (pressed)
			{
				activeCamera->HandleKeyboardInput(FirstPersonCamera::LEFT, bookKeeper->GetDeltaTime());
			}
			break;
		case GLFW_KEY_D:
			if (pressed)
			{
				activeCamera->HandleKeyboardInput(FirstPersonCamera::RIGHT, bookKeeper->GetDeltaTime());
			}
			break;
		}
	}
}

// function to allow keyboard control
// it's called a callback function and must be registerd in main() using glutKeyboardFunc();
// the functions must be of a specific format - see freeglut documentation
// similar functions exist for mouse control etc
void keyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	std::map<int,bool>& keys = keymap;
	if (action == GLFW_PRESS)
	{
		keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}	
	return;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Height = height;
	Width = width;
	glViewport(0, 0, width, height);
}

// Function where we set our debuggables
void ImguiData()
{
	//ImGui new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowSize(ImVec2(400, 200));
	ImGui::Begin("ImGUI window");


	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

}

void ImguiDraw()
{
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main()
{
	Width = 1200;
	Height = 900;
	lastX = Width / 2.0f;
	lastY; Height / 2.0f;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// --------------------
	GLFWwindow* window = glfwCreateWindow(Width, Height, "Scene", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyPress);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// For potential future use
	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	//IMGUI code
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	init();


	while (!glfwWindowShouldClose(window))
	{

		ImguiData();
		bookKeeper->Update(static_cast<float>(glfwGetTime()));
		processInput();
		display(window);
		ImguiDraw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	activeCamera->ProcessMouseMovement(xoffset, yoffset, true);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		Log::WriteLog("Left mouse click", Info);
		FirstPersonCamera* c = static_cast<FirstPersonCamera*>(activeCamera);
		if (c == nullptr) {
			return;
		}

		glm::vec3 rayOrigin = c->GetPosition();
		glm::vec3 rayDirection = c->GetCameraDirection();
		Block* closest = nullptr;
		float closestDistance = std::numeric_limits<float>::max();

		// Check for intersection with each triangle in the model
		for (int i = 0; i < chunks.size(); i++)
		{
			std::vector<Block*> blocks =  chunks[i]->GetBlocks();
			for (auto block : blocks)
			{
				if (!block->IsVisible())
				{
					continue;
				}
				RayIntersectionResult r = RayIntersectionHelper::IsRayIntersectingCube(rayOrigin, rayDirection, block->GetPosition(), 1.0f);

				if (r.IsIntersecting && r.Distance < closestDistance)
				{
					closest = block;
					closestDistance = r.Distance;
				}
			}
		}

		if (closest != nullptr)
		{
			closest->SetVisibility(false);
		}
	}
}