#include "EventManager.h"

template <EventIndex uniqueEventNumber, typename T, typename ... TArgs>
EventHandler<uniqueEventNumber, T, TArgs...>* EventHandler<uniqueEventNumber, T, TArgs...>::instance = nullptr;

void EventLinker::Initialize()
{
	EventHandler<EventIndex::OnUpdate, EventDefines::OnUpdate, int>::GetInstance()->Add(nullptr);
	EventHandler<EventIndex::OnUpdate, EventDefines::OnUpdate, int>::GetInstance()->Remove(nullptr);
	EventHandler<EventIndex::OnRendering, EventDefines::OnRendering, int>::GetInstance()->Add(nullptr);
	EventHandler<EventIndex::OnRendering, EventDefines::OnRendering, int>::GetInstance()->Remove(nullptr);
}