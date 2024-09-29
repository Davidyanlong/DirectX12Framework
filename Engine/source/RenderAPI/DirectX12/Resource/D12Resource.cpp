#include "pch.h"
#include "D12Resource.h"


namespace Engine {
	D12Resource::~D12Resource()
	{
		Release();
	}
	D12Resource::D12Resource(D12Resource&& other) noexcept
	{
		if (other.mMemory) { other->Unmap(0, 0); }
		if (other.Get()) {
			Swap(other);
		}
		if (Get() && other.mMemory) {
			Get()->Map(0, 0, &mMemory);
			other.mMemory = nullptr;
		}
	}
	D12Resource& D12Resource::operator=(D12Resource&& other) noexcept
	{
		if (other.mMemory) { other->Unmap(0, 0); }
		if (other.Get()) {
			Swap(other);
		}
		if (Get() && other.mMemory) {
			Get()->Map(0, 0, &mMemory);
			other.mMemory = nullptr;
		}
		return *this;
	}
	void D12Resource::Initialize(ID3D12Device* pDevice, const unsigned int numBytes, D3D12_HEAP_TYPE heapType, D3D12_RESOURCE_STATES initialState)
	{

		D3D12_HEAP_PROPERTIES heapProp = {};
		heapProp.Type = heapType;
		heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapProp.CreationNodeMask = 0;
		heapProp.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resourceDesc.Alignment = 0;
		resourceDesc.Width = numBytes;
		resourceDesc.Height = 1;
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = 1;
		resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
		resourceDesc.SampleDesc = { 1,0 };
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;


		YT_EVAL_HR(pDevice->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resourceDesc, initialState, 0, IID_PPV_ARGS(GetAddressOf())), "Error creating a resource");
	}

	void D12Resource::InitializeAsDepthBuffer(ID3D12Device* pDevice, const unsigned int width, const unsigned int height)
	{
		D3D12_HEAP_PROPERTIES heapProp = {};
		heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
		heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapProp.CreationNodeMask = 0;
		heapProp.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resDesc = {};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		resDesc.Alignment = 0;
		resDesc.Width = width;
		resDesc.Height = height;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 0;
		resDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		resDesc.SampleDesc = { 1,0 };
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		D3D12_CLEAR_VALUE clearValue = {};
		clearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		clearValue.DepthStencil.Depth = 1.0f;
		clearValue.DepthStencil.Stencil = 0.0f;

		YT_EVAL_HR(pDevice->CreateCommittedResource(&heapProp,D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &clearValue, IID_PPV_ARGS(GetAddressOf())), "Error creating depth buffer");

	}

	void D12Resource::Release()
	{

		if (mMemory && Get())
		{
			Get()->Unmap(0, 0);
			mMemory = nullptr;
		}

		if (Get())
		{

			Reset();
		}
	}

	void* D12Resource::GetCPUMemory()
	{
		if (!mMemory)
		{
			Get()->Map(0, 0, &mMemory);
		}

		return mMemory;
	}



}