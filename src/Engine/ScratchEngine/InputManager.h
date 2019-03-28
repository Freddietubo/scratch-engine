#pragma once
#include <map>
#include "windows.h"

namespace ScratchEngine 
{
	class __declspec(dllexport) InputManager
	{
	private:
		HWND hWnd;
		char* mem;
		std::map<PBYTE, bool> mapOfKeyCodes;
		POINT mPos;
	public:
		// keyboard input
		bool IsKeyDown(char);
		bool IsKeyDown(PBYTE);
		bool SetKeyState(char, bool);
		void Clear();

		// mouse input
		void OnMouseDown(WPARAM, int, int);
		void OnMouseUp(WPARAM, int, int);
		void OnMouseDrag(WPARAM);
	};
}