#pragma once

#include "../Renderer/Renderer.h"

struct ID3D10Device;
struct IDXGISwapChain;
struct ID3D10RenderTargetView;
struct ID3D10DepthStencilView;
struct ID3D10Texture2D;

class D3D10Renderer:public IRenderer
{
public:
	D3D10Renderer();
	~D3D10Renderer();
	bool init(void *pWindowHandle,bool fullScreen);
	void clear(float r,float g,float b,float a);
	void present();
private:
	ID3D10Device * m_pD3D10Device;
	IDXGISwapChain * m_pSwapChain;
	ID3D10RenderTargetView * m_pRenderTargetView;
	ID3D10DepthStencilView * m_pDepthStencelView;
	ID3D10Texture2D *m_pDepthStencilTexture;
};