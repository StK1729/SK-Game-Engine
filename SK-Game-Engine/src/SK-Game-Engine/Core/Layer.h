#pragma once
#include "Core.h"
#include "SK-Game-Engine/Events/Event.h"
#include "SK-Game-Engine/Core/TimeStep.h"

namespace SK_Game_Engine {
	class SKGE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(const Timestep& timestep) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
