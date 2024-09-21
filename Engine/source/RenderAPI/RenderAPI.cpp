#include "pch.h"
#include "RenderAPI.h"

#include <vector>

#include "DirectX12/DXGI/DXGIFactory.h"
#include "DirectX12/DXGI/DXGIAdapter.h"


#include "DirectX12/Debug/D12Debug.h"

#include "../Utilities/Utilities.h"





namespace Engine {
	using namespace Render;


	RenderAPI::~RenderAPI()
	{
		Release();
	}

	void RenderAPI::Initialize(HWND hwnd, const UINT width, const UINT height)
	{
		mWidth = width;
		mHeight = height;

		//this could be disabled during non-debug-builds
		D12Debug::Get().Enable();

		DXGIFactory factory;
		DXGIAdapter adapter = factory.GetAdapter();

		/* CONSOLE OUTPUT FOR DEBUGGING */
		{
			DXGI_ADAPTER_DESC desc;
			adapter->GetDesc(&desc);
			PRINT_W_N("Selected device " << desc.Description);
		}
		/* END DEBUGGING OUTPUT */

		mDevice.Init(adapter.Get());
		mDevice->SetName(L"Main virtual device");

		mCommandQueue.Initialize(mDevice.Get());
		mCommandList.Initialize(mDevice.Get());

		mSwapChain.Initialize(mDevice.Get(), factory.Get(), mCommandQueue.Get(), hwnd, mWidth, mHeight);

		mDynamicVertexBuffer.Initialize(mDevice.Get(), KBs(16), D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
		mDynamicVertexBuffer.Get()->SetName(L"Dynamic vertex buffer");



		/*

		RIGHT NOW FOR SCREEN SPACE COORDINATES VERTICES ONLY HAVE X AND Y mapped to (-1,1) -> (1,-1)

		*/

		std::vector<Vertex> vertices;

#define G_BOX_VERTICES 30
		Vertex verticesbox[G_BOX_VERTICES];

		// front
		verticesbox[0].position = { -1.0f,-1.0f,-1.0f };
		verticesbox[0].color = { 0.0f,1.0f,0.0f,1.0f };
		verticesbox[1].position = { -1.0f,1.0f,-1.0f };
		verticesbox[1].color = { 0.0f,1.0f,0.0f,1.0f };
		verticesbox[2].position = { 1.0f,-1.0f,-1.0f };
		verticesbox[2].color = { 0.0f,1.0f,0.0f,1.0f };

		verticesbox[3].position = { -1.0f,1.0f,-1.0f };
		verticesbox[3].color = { 0.0f,1.0f,0.0f,1.0f };
		verticesbox[4].position = { 1.0f,1.0f,-1.0f };
		verticesbox[4].color = { 0.0f,1.0f,0.0f,1.0f };
		verticesbox[5].position = { 1.0f,-1.0f,-1.0f };
		verticesbox[5].color = { 0.0f,1.0f,0.0f,1.0f };


		// back
		verticesbox[6].position = { -1.0f,1.0f,1.0f };
		verticesbox[6].color = { 1.0f,0.0f,0.0f,1.0f };
		verticesbox[7].position = { -1.0f,-1.0f,1.0f };
		verticesbox[7].color = { 1.0f,1.0f,0.0f,1.0f };
		verticesbox[8].position = { 1.0f,1.0f,1.0f };
		verticesbox[8].color = { 1.0f,1.0f,0.0f,1.0f };

		verticesbox[9].position = { -1.0f,-1.0f,1.0f };
		verticesbox[9].color = { 1.0f,1.0f,0.0f,1.0f };
		verticesbox[10].position = { 1.0f,-1.0f,1.0f };
		verticesbox[10].color = { 1.0f,1.0f,0.0f,1.0f };
		verticesbox[11].position = { 1.0f,1.0f,1.0f };
		verticesbox[11].color = { 1.0f,1.0f,0.0f,1.0f };


		// left
		verticesbox[12].position = { -1.0f,-1.0f,1.0f };
		verticesbox[12].color = { 0.0f,0.0f,1.0f,1.0f };
		verticesbox[13].position = { -1.0f,1.0f,1.0f };
		verticesbox[13].color = { 0.0f,0.0f,1.0f,1.0f };
		verticesbox[14].position = { -1.0f,-1.0f,-1.0f };
		verticesbox[14].color = { 0.0f,0.0f,1.0f,1.0f };


		verticesbox[15].position = { -1.0f,1.0f,1.0f };
		verticesbox[15].color = { 0.0f,1.0f,1.0f,1.0f };
		verticesbox[16].position = { -1.0f,1.0f,-1.0f };
		verticesbox[16].color = { 0.0f,1.0f,1.0f,1.0f };
		verticesbox[17].position = { -1.0f,-1.0f,-1.0f };
		verticesbox[17].color = { 0.0f,1.0f,1.0f,1.0f };

		// right
		verticesbox[18].position = { 1.0f,-1.0f,1.0f };
		verticesbox[18].color = { 0.0f,0.0f,1.0f,1.0f };
		verticesbox[19].position = { 1.0f,-1.0f,-1.0f };
		verticesbox[19].color = { 0.0f,0.0f,1.0f,1.0f };
		verticesbox[20].position = { 1.0f,1.0f,1.0f };
		verticesbox[20].color = { 0.0f,0.0f,1.0f,1.0f };

		verticesbox[21].position = { 1.0f,1.0f,1.0f };
		verticesbox[21].color = { 0.0f,1.0f,1.0f,1.0f };
		verticesbox[22].position = { 1.0f,-1.0f,-1.0f };
		verticesbox[22].color = { 0.0f,1.0f,1.0f,1.0f };
		verticesbox[23].position = { 1.0f,1.0f,-1.0f };
		verticesbox[23].color = { 0.0f,1.0f,1.0f,1.0f };

		// bottom
		verticesbox[24].position = { -1.0f,-1.0f,-1.0f };
		verticesbox[24].color = { 1.0f,0.0f,1.0f,1.0f };
		verticesbox[25].position = { -1.0f,-1.0f,1.0f };
		verticesbox[25].color = { 1.0f,0.0f,1.0f,1.0f };
		verticesbox[26].position = { 1.0f,-1.0f,-1.0f };
		verticesbox[26].color = { 1.0f,0.0f,1.0f,1.0f };

		verticesbox[27].position = { -1.0f,-1.0f,1.0f };
		verticesbox[27].color = { 1.0f,0.0f,1.0f,1.0f };
		verticesbox[28].position = { 1.0f,-1.0f,1.0f };
		verticesbox[28].color = { 1.0f,0.0f,1.0f,1.0f };
		verticesbox[29].position = { 1.0f,-1.0f,-1.0f };
		verticesbox[29].color = { 1.0f,0.0f,1.0f,1.0f };




		memcpy(mDynamicVertexBuffer.GetCPUMemory(), verticesbox, sizeof(Vertex) * G_BOX_VERTICES);



		mDynamicVBView.BufferLocation = mDynamicVertexBuffer.Get()->GetGPUVirtualAddress();
		mDynamicVBView.StrideInBytes = sizeof(Vertex);
		mDynamicVBView.SizeInBytes = KBs(16);



		mBasePipeline.Initialize(mDevice.Get());

		mDepthBuffer.InitializeAsDepthBuffer(mDevice.Get(), mWidth, mHeight);

		mDepthDescHeap.InitializeDepthHeap(mDevice.Get());

		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;
		dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

		mDevice->CreateDepthStencilView(mDepthBuffer.Get(), &dsvDesc, mDepthDescHeap.Get()->GetCPUDescriptorHandleForHeapStart());


		mViewport.TopLeftX = 0;
		mViewport.TopLeftY = 0;
		mViewport.Width = mWidth;
		mViewport.Height = mHeight;
		mViewport.MinDepth = 0.0f;
		mViewport.MaxDepth = 1.0f;

		mSRRect.left = 0;
		mSRRect.right = mViewport.Width;
		mSRRect.top = 0;
		mSRRect.bottom = mViewport.Height;


		DirectX::XMMATRIX viewMatrix;

		viewMatrix = DirectX::XMMatrixLookAtLH({ 0.0f,3.0f,-1.2f }, { 0.0f,0.0f,0.0f }, { 0.0f, 1.0f, 0.0f });

		DirectX::XMMATRIX projectionMatrix;

		projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(1.22173047f, 16.0f / 9.0f, 1, 50.0);

		mViewProjectionMatrix = viewMatrix * projectionMatrix;

		mCBPassData.Initialize(mDevice.Get(), Utils::CalculateConstantbufferAlignment(sizeof(PassData)), D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);




		/*
		OUTLINE FOR THE NEXT STEPS:

		Bind the rendertaget to every part of our outputmerger - check

		We want to bind the rootsignature and pipeline to the GPU / draw proces - check
		Tell how to interpret the data -> set the primitive topology - check


		Bind a datastorage to the "pipeline"/input assembler and give it a view (vertex buffer view) [check]

		DrawCall [check]

		Viewport

		Scissor rect

		*/



	}

	void RenderAPI::UpdateDraw()
	{

		memcpy(mCBPassData.GetCPUMemory(), &mViewProjectionMatrix, sizeof(PassData));
		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = mSwapChain.GetCurrentRenderTarget();
		barrier.Transition.Subresource = 0;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

		mCommandList.GFXCmd()->ResourceBarrier(1, &barrier);

		const float clearColor[] = { 0.0f,0.0f,0.0f,1.0f };
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = mSwapChain.GetCurrentRTVHandle();
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = mDepthDescHeap->GetCPUDescriptorHandleForHeapStart();


		mCommandList.GFXCmd()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, 0);
		mCommandList.GFXCmd()->ClearRenderTargetView(rtvHandle, clearColor, 0, 0);
		mCommandList.GFXCmd()->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

		mCommandList.GFXCmd()->RSSetViewports(1, &mViewport);
		mCommandList.GFXCmd()->RSSetScissorRects(1, &mSRRect);



		mCommandList.GFXCmd()->SetGraphicsRootSignature(mBasePipeline.GetRS());
		mCommandList.GFXCmd()->SetPipelineState(mBasePipeline.Get());
		mCommandList.GFXCmd()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mCommandList.GFXCmd()->IASetVertexBuffers(0, 1, &mDynamicVBView);


		mCommandList.GFXCmd()->SetGraphicsRootConstantBufferView(0, mCBPassData.Get()->GetGPUVirtualAddress());

		mCommandList.GFXCmd()->DrawInstanced(G_BOX_VERTICES, 1, 0, 0);

		barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = mSwapChain.GetCurrentRenderTarget();
		barrier.Transition.Subresource = 0;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

		mCommandList.GFXCmd()->ResourceBarrier(1, &barrier);


		mCommandList.GFXCmd()->Close();
		mCommandQueue.M_ExecuteCommandList(mCommandList.Get());

		mSwapChain.Present();

		while (mCommandQueue.GetFence()->GetCompletedValue() < mCommandQueue.M_GetCurrentFenceValue()) {

			_mm_pause();
		}

		mCommandList.ResetCommandList();
	}

	void RenderAPI::Release()
	{

		mDynamicVertexBuffer.Release();

		mCommandQueue.FlushQueue();

		mSwapChain.Release();

		mCommandList.Release();

		mCommandQueue.Release();


		if (mDevice.Get()) {

			mDevice.Reset();

		}
	}

}