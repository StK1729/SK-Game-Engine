#include "pch.h"
#include "ImGuiLayer.h"
#include "SK-Game-Engine/Application.h"
#include "SK-Game-Engine/KeyCodes.h"

// Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Platform/OpenGL/ImGuiRenderer.h"

namespace SK_Game_Engine
{
	
	ImGuiLayer::ImGuiLayer() 
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f/60.0f);
		static bool show = true;

		ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow(&show);
		float f[] = { 0.2f, 0.3f, 0.8f, 1.0f };
		ImGui::ColorEdit4("Color Label", f);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = SK_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = SK_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = SK_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = SK_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = SK_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = SK_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = SK_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = SK_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = SK_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = SK_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = SK_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = SK_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = SK_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = SK_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = SK_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = SK_KEY_A;
		io.KeyMap[ImGuiKey_C] = SK_KEY_C;
		io.KeyMap[ImGuiKey_V] = SK_KEY_V;
		io.KeyMap[ImGuiKey_X] = SK_KEY_X;
		io.KeyMap[ImGuiKey_Y] = SK_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = SK_KEY_Z;

		//Window& w = Application::Get().GetWindow();
		//ImGui_ImplGlfw_InitForOpenGL(w.GetNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(SKGE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(SKGE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(SKGE_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(SKGE_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(SKGE_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(SKGE_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(SKGE_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(SKGE_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[SK_KEY_LEFT_CONTROL] || io.KeysDown[SK_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[SK_KEY_LEFT_SHIFT] || io.KeysDown[SK_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[SK_KEY_LEFT_ALT] || io.KeysDown[SK_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[SK_KEY_LEFT_SUPER] || io.KeysDown[SK_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;
		return false;
	}

	bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000) {
			io.AddInputCharacter((unsigned short)keycode);
		}

		return false;
	}

}
