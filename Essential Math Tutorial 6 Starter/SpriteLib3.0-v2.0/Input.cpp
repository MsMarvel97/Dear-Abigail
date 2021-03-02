#include "Input.h"

//Sets all of the key flags to initial input of zero
char Input::m_keyWasPressed[256] = { 0 };
char Input::m_keyPressedPreviousFlag[256] = { 0 };

bool Input::m_windowFocus = true;

void Input::UpdateKeys()
{
	for (int i = 0; i < 255; i++)
	{
		m_keyPressedPreviousFlag[i] = m_keyWasPressed[i];
		bool pressed = (GetAsyncKeyState(i) >> 15) & 1;
		m_keyWasPressed[i] = pressed;
	}
}

bool Input::GetKey(Key::In inputKey)
{
	return m_keyWasPressed[inputKey];
}

bool Input::GetKeyDown(Key::In inputKey)
{
	if (m_keyWasPressed[inputKey])
	{
		if (m_keyPressedPreviousFlag[inputKey] == false)
		{
			return true;
		}
	}
	return false;
}

bool Input::GetKeyUp(Key::In inputKey)
{
	if (m_keyWasPressed[inputKey] == false)
	{
		if (m_keyPressedPreviousFlag[inputKey])
		{
			return true;
		}
	}
	return false;
}
