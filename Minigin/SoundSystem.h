#pragma once
#include <string>

namespace dae
{

	using SoundId = unsigned short;

	struct PlayMessage
	{
		std::string name;
		int volume;
	};
	class SoundSystem
	{
		//SoundSystem(const SoundSystem& other) = delete;
		//SoundSystem(SoundSystem&& other) = delete;
		//SoundSystem& operator=(const SoundSystem& other) = delete;
		//SoundSystem& operator=(SoundSystem&& other) = delete;
	public:
		SoundSystem()
		{
			m_Head = 0;
			m_Tail = 0;
		}
		virtual ~SoundSystem();

		virtual void Update() = 0;

		virtual void play(const std::string name, const int volume) = 0;
		std::string m_dataPath = "../Data/";

	protected:
		static const int MAX_PENDING = 16;

		PlayMessage pending_[MAX_PENDING];
		int numPending_;

		int m_Head;
		int m_Tail;
	};
}