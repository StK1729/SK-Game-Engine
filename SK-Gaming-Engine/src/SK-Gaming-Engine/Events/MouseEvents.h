#pragma once
#include "pch.h"
#include "Event.h"


namespace SK_Gaming_Engine
{
	class SKGE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(double x, double y) : m_mouseX{ x }, m_mouseY{ y }
		{}

		inline double GetX() { return m_mouseX; }
		inline double GetY() { return m_mouseY; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMoveEvent: " << m_mouseX << ", " << m_mouseY;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		double m_mouseX, m_mouseY;
	};

	class SKGE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(double xOffset, double yOffset) : m_XOffset{ xOffset }, m_YOffset{ yOffset }
		{}

		inline double GetXOffset() { return m_XOffset; }
		inline double GetYOffset() { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		double m_XOffset, m_YOffset;
	};

	class SKGE_API MouseButtonEvent : public Event
	{
	public:
		
		inline int GetMouseButton() { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int button) : m_button{button}
		{}
		int m_button;
	};

	class SKGE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class SKGE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}