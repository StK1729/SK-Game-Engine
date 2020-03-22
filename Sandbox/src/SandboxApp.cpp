#include <SKGE.h>
#include <memory>


class Sandbox : public SK_Gaming_Engine::Application
{
public:
	Sandbox() 
	{

	}
	~Sandbox()
	{

	}
};

SK_Gaming_Engine::Application* SK_Gaming_Engine::CreateApplication()
{
	return new Sandbox();
}