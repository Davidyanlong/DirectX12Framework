#pragma once
#include <wrl.h>

#include <dxgidebug.h>

namespace Engine {
	class DXGIDebug	: public Microsoft::WRL::ComPtr<IDXGIDebug>
	{
	public:
		DXGIDebug() = default;

		void Enable();

		void GetLiveObjects();

	public:
		static inline DXGIDebug& Get(){ return mInstance; }

	private:

		void GetInterface();

	private:
		static DXGIDebug mInstance;
	};

}
