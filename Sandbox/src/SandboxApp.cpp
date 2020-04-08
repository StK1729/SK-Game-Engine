#include <SKGE.h>
#include <memory>


class ExampleLayer : public SK_Gaming_Engine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}
	void OnUpdate() override
	{
		SKGE_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(SK_Gaming_Engine::Event& event) override 
	{
		SKGE_CLIENT_TRACE("{0}", event);
	}
};

class Sandbox : public SK_Gaming_Engine::Application
{
public:
	Sandbox() 
	{
		PushOverlay(new SK_Gaming_Engine::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

SK_Gaming_Engine::Application* SK_Gaming_Engine::CreateApplication()
{
	return new Sandbox();
}