#include <SKGE.h>
#include <memory>


class ExampleLayer : public SK_Game_Engine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}
	void OnUpdate() override
	{
		SKGE_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(SK_Game_Engine::Event& event) override 
	{
		SKGE_CLIENT_TRACE("{0}", event);
	}
};

class Sandbox : public SK_Game_Engine::Application
{
public:
	Sandbox() 
	{
		PushOverlay(new SK_Game_Engine::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

SK_Game_Engine::Application* SK_Game_Engine::CreateApplication()
{
	return new Sandbox();
}