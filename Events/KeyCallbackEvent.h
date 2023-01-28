#pragma once

#include "Event.h"

class KeyCallbackEvent : public Event
{
private:
	int m_key;
	int m_scancode;
	int m_mods;
	int m_action;

	KeyCallbackEvent();
public:
	KeyCallbackEvent(int key, int scancode, int action, int mods)
		: m_key(key), m_scancode(scancode), m_action(action), m_mods(mods)
	{}

	const int& GetKey() const { return m_key; }
	const int& GetScanCode() const { return m_scancode; }
	const int& GetAction() const { return m_action; }
	const int& GetMods() const { return m_mods; }
};