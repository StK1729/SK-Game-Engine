#pragma once


namespace SK_Game_Engine
{
	class Timestep
	{
	public:
		Timestep(float time)
			: m_Time{ time }
		{}
		inline float GetSeconds() const { return m_Time; }
		inline float GetMilliSeconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}