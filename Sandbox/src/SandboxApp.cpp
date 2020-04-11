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
};

class Sandbox : public SK_Game_Engine::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
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