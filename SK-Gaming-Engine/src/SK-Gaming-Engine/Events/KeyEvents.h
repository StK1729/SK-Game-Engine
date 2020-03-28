#pragma once
#include "pch.h"
#include "Event.h"


namespace SK_Gaming_Engine
{
	class SKGE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() { return m_keyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
	protected:
		KeyEvent(int keycode) : m_keyCode{ keycode }
		{ }

		int m_keyCode;
	};

	class SKGE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent{ keycode }, m_repeatCount{ repeatCount }
		{ }
		inline int GetRepeatCount() { return m_repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

		
	protected:
		int m_repeatCount;
	};

	class SKGE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode)
		{}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
	};
}