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
#include "Texture.h"
#include "Projection.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

//int Width;
//int Height;
using namespace std;

std::vector<Chunk*> chunks;
Block* b;
Shader* activeShader;
//ICamera* activeCamera;
FirstPersonCamera* activeCamera = new FirstPersonCamera(glm::vec3(0.0f, 0.0f, -5.0f));
LightSource* lighting;
Texture* testTex; 
std::vector<Texture*> testTexs;
Utility* bookKeeper;
bool firstMouse = true;
float lastX; //= SCR_WIDTH / 2.0f;
float lastY;// = SCR_HEIGHT / 2.0f;
std::map<int,bool> keymap;

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

	//glm::mat4 projection = GetProjection();

	activeShader->SetLighting(lighting);
	//activeShader->SetUniform1f("time", timeValue);
	//activeShader->SetUniform1f("rand", r);
	//activeShader->SetUniformMatrix4fv("projection", &projection);
	
	// Remove chunks if they are too far away
	glm::vec3 PlayerChunkCoordinate = Chunk::GlobalToChunkCoordinate(activeCamera->GetPosition());
	chunks.erase(std::remove_if(chunks.begin(), chunks.end(),
		[&](Chunk* c) 
		{
			float distance = glm::distance(PlayerChunkCoordinate, c->GetPosition());
			if (distance > Constants::RADIUS_GENERATION)
				return true;
			return false;
		}), chunks.end());

	// Add new chunks to load based on the current player position.
	// Do a loop for coordinates around the player to see if we can add any chunks.
	for (int i = -Constants::RADIUS_GENERATION; i < Constants::RADIUS_GENERATION; i++)
	{
		for (int j = -Constants::RADIUS_GENERATION; j < Constants::RADIUS_GENERATION; j++)
		{
			glm::vec3 chunkCoordinate = glm::vec3(PlayerChunkCoordinate.x,0, PlayerChunkCoordinate.z) + glm::vec3(i, 0, j);
			float distance = glm::distance(PlayerChunkCoordinate, chunkCoordinate);
			if (distance > Constants::RADIUS_GENERATION)
				continue;

			auto chunk = std::find_if(
				chunks.begin(),
				chunks.end(),
				[&](Chunk* c) {
					return c->GetPosition() == chunkCoordinate;
				});

			if (chunk != chunks.end())
			{
			}
			else
			{
				chunks.push_back(new Chunk(chunkCoordinate, *b));
			}

		}
	}

	for (auto c : chunks)
	{
		float distance = glm::distance(activeCamera->GetPosition(), c->GetChunkGlobalCoordinate());
		
		if (distance > Constants::RADIUS_GENERATION)
		{
			//v.erase(std::remove_if(v.begin(), v.end(),
			//	[](int i) { return i < 10; }), v.end());
		}
	}

	for (auto c : chunks)
	{
		c->Draw();
	}

}

void UpdateViewData() {
	activeShader->SetUniformMatrix4fv("view", activeCamera->GetViewTransform());
	activeShader->SetUniformVec3("ViewPosition", activeCamera->GetPosition());
}

void LoadShaders()
{
	//activeShader = new Shader("./blinnPhong.vert", "./blinnPhong.frag");
	activeShader = new Shader("./textureTest.vert", "./textureTest.frag");
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
	b = new Block(activeShader, testTexs);

	//chunk = new Chunk(glm::vec3(0,0,0), *b);

	chunks = std::vector<Chunk*>();
	//chunks.push_back(chunk);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			chunks.push_back(new Chunk(glm::vec3(i, 0, j), *b));
		}
	}
}

void initLight()
{
	lighting = new LightSource(glm::vec3(10, 100, 10), glm::vec3(1, 1, 1));
}

void initTexture() {
	const char* path = "./DiamondTexture.png";

	std::vector<const char*> paths = {"./CoalTexture.png", "./DiamondTexture.png", "./DirtTexture.png", "./GoldTexture.png", "./RedstoneTexture.png", "./SilverTexture.png"};

	for (int i = 0; i < paths.size(); i++) 
	{
		testTexs.push_back(new Texture(paths[i]));
	}

	//testTex = new Texture(path);
	activeShader->SetUniform1i("TextureSlot", 0);
}

void initUtility() 
{
	bookKeeper = new Utility(); 
}

void initProjection()
{
	glm::mat4 projection = Projection::GetProjection();
	activeShader->SetUniformMatrix4fv("projection", &projection);
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
	initTexture();
	LoadCameras();
	LoadObjects();
	initProjection();
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
				UpdateViewData();
			}
			break;
		case GLFW_KEY_S:
			if (pressed)
			{
				activeCamera->HandleKeyboardInput(FirstPersonCamera::BACK, bookKeeper->GetDeltaTime());
				UpdateViewData();
			}
			break;
		case GLFW_KEY_A:
			if (pressed)
			{
				activeCamera->HandleKeyboardInput(FirstPersonCamera::LEFT, bookKeeper->GetDeltaTime());
				UpdateViewData();
			}
			break;
		case GLFW_KEY_D:
			if (pressed)
			{
				activeCamera->HandleKeyboardInput(FirstPersonCamera::RIGHT, bookKeeper->GetDeltaTime());
				UpdateViewData();
			}
			break;
		case GLFW_KEY_C:
			if (pressed)
			{
				activeCamera->HandleKeyboardInput(FirstPersonCamera::DOWN, bookKeeper->GetDeltaTime());
				UpdateViewData();
			}
			break;
		case GLFW_KEY_SPACE:
			if (pressed)
			{
				activeCamera->HandleKeyboardInput(FirstPersonCamera::UP, bookKeeper->GetDeltaTime());
				UpdateViewData();
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
	Projection::Height = height;
	Projection::Width = width;
	glViewport(0, 0, Projection::fovy, Projection::Height);
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
	Projection::Width = 1200;
	Projection::Height = 900;
	lastX = Projection::Width / 2.0f;
	lastY = Projection::Height / 2.0f;



	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// --------------------
	GLFWwindow* window = glfwCreateWindow(Projection::Width, Projection::Height, "Scene", NULL, NULL);

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
	UpdateViewData();
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