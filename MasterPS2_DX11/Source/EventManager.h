#pragma once
#include <vector>
#include <functional>
#include <d3d11.h>

#ifndef N_MANAGED_BUILD
#include <ppl.h>
#include <future>
#endif


enum class EventIndex
{
	OnUpdate = 1,
	OnRendering = 2
};

namespace EventDefines
{
	typedef void(OnUpdate)(int);
	//Drawing
	typedef HRESULT(OnRendering)(int);
}

class EventLinker
{
public:
	static void Initialize();
};

#define EVENT_TIMEOUT_EJECT 250

// ReSharper disable once CppClassNeedsConstructorBecauseOfUninitializedMember
template <EventIndex uniqueEventNumber, typename T, typename ... TArgs>
class EventHandler
{
	std::vector<void*> m_EventCallbacks;
	DWORD t_RemovalTickCount;
	static EventHandler* instance;
public:
	static EventHandler* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new EventHandler();
		}

		return instance;
	}

	void Add(void* callback)
	{
		if (callback != nullptr)
		{
			m_EventCallbacks.push_back(callback);
		}
	}

	void Remove(void* listener)
	{
		if (listener == nullptr)
		{
			return;
		}

		auto eventPtr = find(m_EventCallbacks.begin(), m_EventCallbacks.end(), listener);
		if (eventPtr != m_EventCallbacks.end())
		{
			m_EventCallbacks.erase(find(m_EventCallbacks.begin(), m_EventCallbacks.end(), listener));
		}

		this->t_RemovalTickCount = GetTickCount();
	}

	bool __cdecl TriggerProcess(TArgs... args)
	{
		auto process = true;
		auto tickCount = GetTickCount();

		for (auto ptr : m_EventCallbacks)
		{
			if (ptr != nullptr)
			{
				if (tickCount - t_RemovalTickCount > EVENT_TIMEOUT_EJECT)
				{
					if (!static_cast<T*>(ptr) (args...))
					{
						process = false;
					}
				}
			}
		}

		return process;
	}

	bool __cdecl Trigger(TArgs... args)
	{
		auto tickCount = GetTickCount();

		for (auto ptr : m_EventCallbacks)
		{
			if (ptr != nullptr)
			{
				if (tickCount - t_RemovalTickCount > EVENT_TIMEOUT_EJECT)
				{
					static_cast<T*>(ptr) (args...);
				}
			}
		}

		return true;
	}
};




