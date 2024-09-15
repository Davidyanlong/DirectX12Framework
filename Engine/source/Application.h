#pragma once

#include <Windows.h>
#include "EngineMin.h"

namespace Engine {
	class YT_API Application
	{
	public:
		Application() = default;

		bool Initialize();

		void OnCreate(HWND hwnd);

		void Update();

		void OnDestroy();

		inline bool IsRunning() { return mIsRunning; }

	private:
		bool mIsRunning = false;
		HWND mWindowHandle = nullptr;
	};

}