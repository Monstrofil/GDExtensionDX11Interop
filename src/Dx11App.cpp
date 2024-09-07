#pragma once
#include "DX11App.h"



void DX11App::init( VkPhysicalDevice device )
{
    this->pDeviceInfo = this->createDXDevice( device );

    D3D11_TEXTURE2D_DESC textureDescriptor;
    this->createDX11SharedTexture( textureWidth, textureHeight, textureFormat, &textureDescriptor,
                                   this->pDeviceInfo->getDevice(), &this->pRenderTargetTexture,
                                   &renderTargetHandle );
}

void DX11App::fini()
{
    renderTargetHandle = NULL;

    if ( pRenderTargetTexture )
    {
        pRenderTargetTexture->Release();
    }

    if ( pDeviceInfo && pDeviceInfo->getDeviceContext() )
    {
        pDeviceInfo->getDeviceContext()->ClearState(); // Ensures no pipeline resources are bound
        pDeviceInfo->getDeviceContext()->Flush();      // Flushes any pending commands
        pDeviceInfo->getDeviceContext()->Release();    // Releases the context
    }

    if ( pRenderTargetView )
    {
        pRenderTargetView = nullptr;
    }

    pDeviceInfo = nullptr;
    
}


void DX11App::draw(int frame)
{
    IDXGIKeyedMutex *pKeyedMutex = nullptr;
    auto hr = this->pRenderTargetTexture->QueryInterface( __uuidof( IDXGIKeyedMutex ),
                                                          (void **)&pKeyedMutex );
    DEV_ASSERT( SUCCEEDED( hr ) );

    UINT64 acquireKey = 0;                                 // Key used to acquire the mutex
    hr = pKeyedMutex->AcquireSync( acquireKey, INFINITE ); // Wait indefinitely to acquire
    DEV_ASSERT( SUCCEEDED( hr ) );

    this->pDeviceInfo->getDeviceContext()->OMSetRenderTargets( 1, &pRenderTargetView, nullptr );

    D3D11_VIEWPORT viewport;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = static_cast<float>( this->textureWidth );  // Texture width
    viewport.Height = static_cast<float>( this->textureHeight ); // Texture height
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    this->pDeviceInfo->getDeviceContext()->RSSetViewports( 1, &viewport );

    uint32_t frameIndex = frame;

    float clearColor[4] = { (float)fabs( (float)cos( 50.0 + frameIndex / 100.f ) ),
                            (float)fabs( (float)sin( frameIndex / 200.f ) ),
                            (float)fabs( (float)sin( 100.0 + frameIndex / 100.f ) ), 1.0f }; // RGBA random
    this->pDeviceInfo->getDeviceContext()->ClearRenderTargetView( pRenderTargetView,
                                                                  clearColor );

    ID3D11RenderTargetView *nullViews[] = { nullptr };
    this->pDeviceInfo->getDeviceContext()->OMSetRenderTargets( 1, nullViews, nullptr );

    hr = pKeyedMutex->ReleaseSync( acquireKey ); // Release the mutex
    DEV_ASSERT( SUCCEEDED( hr ) );
}


D3D11Device *DX11App::createDXDevice( VkPhysicalDevice physicalDevice )
{
    IDXGIFactory1 *pFactory;
    HRESULT hr = CreateDXGIFactory1( __uuidof( IDXGIFactory1 ), (void **)( &pFactory ) );

    DEV_ASSERT( hr == S_OK );

    uint32_t i = 0;
    IDXGIAdapter *pAdapter;
    std::vector<IDXGIAdapter *> vAdapters;

    while ( pFactory->EnumAdapters( i, &pAdapter ) != DXGI_ERROR_NOT_FOUND )
    {
        vAdapters.push_back( pAdapter );
        ++i;
    }

    for ( i = 0; i < vAdapters.size(); ++i )
    {
        DXGI_ADAPTER_DESC adapterDesc;
        vAdapters[i]->GetDesc( &adapterDesc );
    }

    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties( physicalDevice, &properties );

    uint32_t searchVendorId = properties.vendorID;
    uint32_t searchDeviceId = properties.deviceID;

    for ( i = 0; i < vAdapters.size(); ++i )
    {
        ID3D11Device *pDevice = nullptr;
        ID3D11DeviceContext *pDeviceContext = nullptr;

        // D3D11_CREATE_DEVICE_DEBUG

        HRESULT result =
            D3D11CreateDevice( vAdapters[i],            // nullptr
                               D3D_DRIVER_TYPE_UNKNOWN, // D3D_DRIVER_TYPE_HARDWARE,
                               nullptr,
                               D3D11_CREATE_DEVICE_DEBUG, // 0,
                               nullptr,                   // D3D_FEATURE_LEVEL_11_1
                               0, D3D11_SDK_VERSION, &pDevice, nullptr, &pDeviceContext );

        if ( S_OK == result )
        {
            DXGI_ADAPTER_DESC adapterDesc;
            vAdapters[i]->GetDesc( &adapterDesc );

            if ( searchVendorId != adapterDesc.VendorId )
            {
                continue;
            }

            if ( searchDeviceId != adapterDesc.DeviceId )
            {
                continue;
            }

            return new D3D11Device( &adapterDesc, pDevice, pDeviceContext );
        }
    }

    return nullptr;
}


void DX11App::createDX11SharedTexture( uint32_t imageWidth, uint32_t imageHeight,
                                       DXGI_FORMAT format,
                                       D3D11_TEXTURE2D_DESC *pDescColor, ID3D11Device *pd3d11Device,
                                       ID3D11Texture2D **ppd3dTexture, HANDLE *pSharedHandle )
{
    memset( pDescColor, 0, sizeof( D3D11_TEXTURE2D_DESC ) );
    pDescColor->Width = imageWidth;
    pDescColor->Height = imageHeight;
    pDescColor->MipLevels = 1;
    pDescColor->ArraySize = 1;
    pDescColor->Format = format;
    pDescColor->SampleDesc.Count = 1;
    pDescColor->SampleDesc.Quality = 0;
    pDescColor->Usage = D3D11_USAGE_DEFAULT;
    pDescColor->BindFlags = D3D11_BIND_RENDER_TARGET;
    pDescColor->CPUAccessFlags = 0; // D3D11_CPU_ACCESS_READ if you want to read it with CPU

    pDescColor->MiscFlags =
        D3D11_RESOURCE_MISC_SHARED_NTHANDLE | D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;

    // Blue color data (RGBA)
    const UINT textureSize =
        imageWidth * imageHeight * 4; 
    unsigned char *blueData = new unsigned char[textureSize];
    for ( UINT i = 0; i < imageHeight * imageWidth; ++i )
    {
        blueData[i] = 0;        // Red channel
        blueData[i + 1] = 0;    // Green channel
        blueData[i + 2] = 255;  // Blue channel
        blueData[i + 3] = 0;    // Alpha channel (fully opaque)
    }

    // Define the subresource data
    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = blueData;           // Pointer to texture data
    initData.SysMemPitch = imageWidth * 4; // Pitch of the data (width * 4 bytes per pixel)

    HRESULT result = pd3d11Device->CreateTexture2D( pDescColor, &initData, ppd3dTexture );
    DEV_ASSERT( result == S_OK );

    // create render target so we can update this texture
    auto hr = this->pDeviceInfo->getDevice()->CreateRenderTargetView(
        this->pRenderTargetTexture.Get(), nullptr, &pRenderTargetView );
    DEV_ASSERT( SUCCEEDED( hr ) );

    *pSharedHandle = 0;

    IDXGIResource1 *tempResource = nullptr;
    ( *ppd3dTexture )->QueryInterface( __uuidof( IDXGIResource1 ), (void **)&tempResource );
    result = tempResource->CreateSharedHandle(
        nullptr, DXGI_SHARED_RESOURCE_READ | DXGI_SHARED_RESOURCE_WRITE, nullptr, pSharedHandle );
    tempResource->Release();
    DEV_ASSERT( result == S_OK );
}