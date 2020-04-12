#include <SKGE.h>
#include <memory>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"


class ExampleLayer : public SK_Game_Engine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}
	void OnUpdate() override
	{
		if (SK_Game_Engine::Input::IsKeyPressed(SK_KEY_TAB)) {
			SKGE_CLIENT_INFO("Tab key was pressed! (poll)");
		}
	}

	void OnEvent(SK_Game_Engine::Event& event) override 
	{
		if (event.GetEventType() == SK_Game_Engine::EventType::KeyPressed) {
			SK_Game_Engine::KeyPressedEvent& kpe = (SK_Game_Engine::KeyPressedEvent&)event;
			if (SK_Game_Engine::Input::IsKeyPressed(SK_KEY_TAB)) {
				SKGE_CLIENT_TRACE("Tab key was pressed! (event)");
			}
		}
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world");
		ImGui::End();
	}
};

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class Sandbox : public SK_Game_Engine::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

SK_Game_Engine::Application* SK_Game_Engine::CreateApplication()
{
	return new Sandbox();
}