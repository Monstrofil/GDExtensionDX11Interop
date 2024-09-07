#pragma once
#include <vector>
#include "d3d11_1.h"

#define VK_USE_PLATFORM_WIN32_KHR
#include "vulkan/vulkan.h"
#include <godot_cpp/core/error_macros.hpp>
#include <wrl.h>


using namespace Microsoft::WRL;


class D3D11Device
{
private:
    DXGI_ADAPTER_DESC adapterDescription;
    ID3D11Device *pDevice;
    ID3D11Device1 *pDevice1;

    ID3D11DeviceContext *pDeviceContext;

public:
    D3D11Device()
    {
    }

    D3D11Device( DXGI_ADAPTER_DESC *pAdapterDesc, ID3D11Device *pDevice,
                 ID3D11DeviceContext *pDeviceContext )
    {
        this->adapterDescription = *pAdapterDesc;
        this->pDevice = pDevice;
        this->pDeviceContext = pDeviceContext;

        HRESULT hr = pDevice->QueryInterface( __uuidof( ID3D11Device1 ), (void **)&pDevice1 );
        DEV_ASSERT( hr == S_OK );
    }

    inline const DXGI_ADAPTER_DESC *getAdapterDesc()
    {
        return &this->adapterDescription;
    }

    inline ID3D11Device *getDevice()
    {
        return this->pDevice;
    }

    inline ID3D11Device1 *getDevice1()
    {
        return this->pDevice1;
    }

    inline ID3D11DeviceContext *getDeviceContext()
    {
        return this->pDeviceContext;
    }
};



class DX11App
{

    private:
        D3D11Device* pDeviceInfo;
        ComPtr<ID3D11Texture2D> pRenderTargetTexture;

        ID3D11RenderTargetView* pRenderTargetView;

	public:
        int textureWidth = 1000;
        int textureHeight = 1000;
        DXGI_FORMAT textureFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

        /* will be updated after init */
        HANDLE renderTargetHandle = NULL;

        void init( VkPhysicalDevice device );
        void fini();

        void draw(int frame);

        /* creates D3D11Device on the same physical device as game runs */
        D3D11Device *DX11App::createDXDevice( VkPhysicalDevice physicalDevice );

        /* creates ID3D11Texture2D and shares it as NTHANDLE (pSharedHandle) */
        void createDX11SharedTexture( uint32_t imageWidth, uint32_t imageHeight, DXGI_FORMAT format,
                                      D3D11_TEXTURE2D_DESC *pDescColor, ID3D11Device *pd3d11Device,
                                      ID3D11Texture2D **ppd3dTexture, HANDLE *pSharedHandle );
};