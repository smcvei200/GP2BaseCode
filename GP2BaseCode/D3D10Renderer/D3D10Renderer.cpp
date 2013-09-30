#include "D3D10Renderer.h"

#include <D3D10.h>
#include <D3DX10.h>

D3D10Renderer::D3D10Renderer()
{
	m_pD3D10Device = NULL;
	m_pRenderTargetView = NULL;
	m_pSwapChain = NULL;
	m_pDepthStencilView = NULL;
	m_pDepthStencilTexture = NULL;
}

D3D10Renderer::~D3D10Renderer()
{
	if(m_pD3D10Device)
		m_pD3D10Device->ClearState();
	if(m_pRenderTargetView)
		m_pRenderTargetView->Release();
	if(m_pDepthStencilView)
		m_pDepthStencilView->Release();
	if(m_pDepthStencilTexture)
		m_pDepthStencilTexture->Release();
	if(m_pSwapChain)
		m_pSwapChain->Release();
	if(m_pD3D10Device)
		m_pD3D10Device->Release();
}

bool D3D10Renderer:: init(void *pWindowHandle, bool fullScreen)
{
	HWND window = (HWND)pWindowHandle;
	RECT windowRect;
	GetClientRect(window, &windowRect);

	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom-windowRect.top;

	if(!createDevice(window, width, height, fullScreen))
		return false;
	if(!createInitialRenderTarget(width, height))
		return false;
	return true;
}

bool D3D10Renderer:: createDevice(HWND window, int windowWidth, int windowHeight, bool fullScreen)
{
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags|= D3D10_CREATE_DEVICE_DEBUG;
#endif

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof( sd) );
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	if(fullScreen)
		sd.BufferCount = 2;
	else
		sd.BufferCount = 1;
	sd.OutputWindow = window;
	sd.Windowed = (BOOL)(!fullScreen);
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferDesc.Width = windowWidth;
	sd.BufferDesc.Height = windowHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;

	if(FAILED(D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE,NULL, createDeviceFlags, D3D10_SDK_VERSION, &sd, &m_pSwapChain, &m_pD3D10Device)))
		return false;

	return true;
}

bool D3D10Renderer::createInitialRenderTarget(int windowWidth, int windowHeight)
{
	ID3D10Texture2D *pBackBuffer;
	if(FAILED(m_pSwapChain->GetBuffer(0,_uuidof(ID3D10Texture2D),(void**)&pBackBuffer)))
		return false;

	D3D10_TEXTURE2D_DESC descDepth;
	descDepth.Width = windowWidth;
	descDepth.Height = windowHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	if(FAILED(m_pD3D10Device->CreateTexture2D(&descDepth, NULL, &m_pDepthStencilTexture)))
		return false;

	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	if(FAILED(m_pD3D10Device-> CreateDepthStencilView(m_pDepthStencilTexture, &descDSV, &m_pDepthStencilView)))
		return false;

	if (FAILED(m_pD3D10Device->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView)))
	{
		pBackBuffer->Release();
		return false;
	}
	pBackBuffer->Release();

	m_pD3D10Device->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	D3D10_VIEWPORT vp;
	vp.Width = windowWidth;
	vp.Height = windowHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pD3D10Device->RSSetViewports(1, &vp);
	return true;
}

void D3D10Renderer::clear(float r, float g, float b, float a)
{
	const float ClearColor[4] = {r,g,b,a};
	m_pD3D10Device-> ClearRenderTargetView(m_pRenderTargetView, ClearColor);
	m_pD3D10Device->ClearDepthStencilView(m_pDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
}

void D3D10Renderer::present()
{
	m_pSwapChain->Present(0, 0);
}

