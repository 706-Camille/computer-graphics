#include "Renderer.h"
#include <d3dcompiler.h>
#include "assert.h"
#include "Debug.h";

void URenderer::Create(HWND hWindow)
{
	CreateDeviceAndSwapChain(hWindow);
	CreateFrameBuffer();
	CreateRasterizerState();
}

void URenderer::CreateDeviceAndSwapChain(HWND hWindow)
{
    HRESULT hr;

    // 지원하는 Direct3D 기능 레벨을 정의
    D3D_FEATURE_LEVEL featurelevels[] = { D3D_FEATURE_LEVEL_11_0 };

    // 스왑 체인 설정 구조체 초기화
    DXGI_SWAP_CHAIN_DESC swapchaindesc = {};
    swapchaindesc.BufferDesc.Width = 0; // 창 크기에 맞게 자동으로 설정
    swapchaindesc.BufferDesc.Height = 0; // 창 크기에 맞게 자동으로 설정
    swapchaindesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // 색상 포맷
    swapchaindesc.SampleDesc.Count = 1; // 멀티 샘플링 비활성화
    swapchaindesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 렌더 타겟으로 사용
    swapchaindesc.BufferCount = 2; // 더블 버퍼링
    swapchaindesc.OutputWindow = hWindow; // 렌더링할 창 핸들
    swapchaindesc.Windowed = TRUE; // 창 모드
    swapchaindesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // 스왑 방식

    // Direct3D 장치와 스왑 체인을 생성
    hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG,
        featurelevels, ARRAYSIZE(featurelevels), D3D11_SDK_VERSION,
        &swapchaindesc, &SwapChain, &Device, nullptr, &DeviceContext);

    HR_CHECK(hr, L"D3D11CreateDeviceAndSwapChain Failed!\n");
    

    // 생성된 스왑 체인의 정보 가져오기
    hr = SwapChain->GetDesc(&swapchaindesc);

    HR_CHECK(hr, L"GetDesc Failed!\n");

    // 뷰포트 정보 설정
    ViewportInfo = { 0.0f, 0.0f, (float)swapchaindesc.BufferDesc.Width, (float)swapchaindesc.BufferDesc.Height, 0.0f, 1.0f };
}

void URenderer::CreateFrameBuffer()
{
    HRESULT hr;
    hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);

    HR_CHECK(hr, L"GetBuffer Failed!\n");

    D3D11_RENDER_TARGET_VIEW_DESC FrameBufferRTVdesc = {};
    FrameBufferRTVdesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB; // 색상 포맷
    FrameBufferRTVdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // 2D 텍스처

    hr = Device->CreateRenderTargetView(FrameBuffer, &FrameBufferRTVdesc, &FrameBufferRTV);
    HR_CHECK(hr, L"CreateRenderTargetView Failed!\n");
}

void URenderer::CreateRasterizerState()
{
    D3D11_RASTERIZER_DESC RasterizerDesc = {};
    RasterizerDesc.FillMode = D3D11_FILL_SOLID;
    RasterizerDesc.CullMode = D3D11_CULL_BACK;

    HRESULT hr = Device->CreateRasterizerState(&RasterizerDesc, &RasterizerState);

    HR_CHECK(hr, L"CreateRasterizerState Failed!\n");
}

void URenderer::CreateShader()
{
    HRESULT hr;

    ID3DBlob* vertexshaderCSO; // Binary Large Object, 셰이더 코드의 바이너리를 담는 버퍼
    ID3DBlob* pixelshaderCSO;

    hr = D3DCompileFromFile(L"ShaderW0.hlsl", nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &vertexshaderCSO, nullptr);
    
    HR_CHECK(hr, L"D3DCompileFromFile Failed!\n");

    hr = Device->CreateVertexShader(vertexshaderCSO->GetBufferPointer(), vertexshaderCSO->GetBufferSize(), nullptr, &SimpleVertexShader);

    HR_CHECK(hr, L"CreateVertexShader Failed!\n");

    hr = D3DCompileFromFile(L"ShaderW0.hlsl", nullptr, nullptr, "mainPS", "ps_5_0", 0, 0, &pixelshaderCSO, nullptr);

    HR_CHECK(hr, L"D3DCompileFromFile Failed!\n");
   
    hr = Device->CreatePixelShader(pixelshaderCSO->GetBufferPointer(), pixelshaderCSO->GetBufferSize(), nullptr, &SimplePixelShader);

    HR_CHECK(hr, L"CreatePixelShader Failed!\n");

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    hr = Device->CreateInputLayout(layout, ARRAYSIZE(layout), vertexshaderCSO->GetBufferPointer(), vertexshaderCSO->GetBufferSize(), &SimpleInputLayout);

    HR_CHECK(hr, L"CreateInputLayout Failed!\n");

    Stride = sizeof(FVertexSimple);

    vertexshaderCSO->Release();
    pixelshaderCSO->Release();
}

ID3D11Buffer* URenderer::CreateVertexBuffer(FVertexSimple* vertices, UINT byteWidth)
{

    D3D11_BUFFER_DESC vertexbufferdesc = {};
    vertexbufferdesc.ByteWidth = byteWidth;
    vertexbufferdesc.Usage = D3D11_USAGE_IMMUTABLE;
    vertexbufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexbufferSRD = { vertices };

    ID3D11Buffer* vertexBuffer;

    Device->CreateBuffer(&vertexbufferdesc, &vertexbufferSRD, &vertexBuffer);

    return vertexBuffer;
}

void URenderer::CreateConstantBuffer()
{
    D3D11_BUFFER_DESC constantbufferdesc = {};
    constantbufferdesc.ByteWidth = sizeof(FConstants) + 0xf & 0xfffffff0; // ensure constant buffer size is multiple of 16 bytes
    constantbufferdesc.Usage = D3D11_USAGE_DYNAMIC; // will be updated from CPU every frame
    constantbufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    constantbufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    Device->CreateBuffer(&constantbufferdesc, nullptr, &ConstantBuffer);

}

// 스왑 체인의 백 버퍼와 프론트 버퍼를 교체하여 화면에 출력
void URenderer::SwapBuffer()
{
    SwapChain->Present(1, 0); // 1: VSync 활성화
}

void URenderer::Prepare()
{
    DeviceContext->ClearRenderTargetView(FrameBufferRTV, ClearColor);

    DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    DeviceContext->RSSetViewports(1, &ViewportInfo);
    DeviceContext->RSSetState(RasterizerState);

    DeviceContext->OMSetRenderTargets(1, &FrameBufferRTV, nullptr);
    DeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}

void URenderer::PrepareShader()
{
    DeviceContext->VSSetShader(SimpleVertexShader, nullptr, 0);
    DeviceContext->PSSetShader(SimplePixelShader, nullptr, 0);
    DeviceContext->IASetInputLayout(SimpleInputLayout);

    if (ConstantBuffer)
    {
        DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);
    }
}

void URenderer::RenderPrimitive(ID3D11Buffer* pBuffer, UINT numVertices)
{
    UINT offset = 0;
    DeviceContext->IASetVertexBuffers(0, 1, &pBuffer, &Stride, &offset);

    DeviceContext->Draw(numVertices, 0);
}

void URenderer::UpdateConstant(FVector Offset)
{
    if (ConstantBuffer)
    {
        D3D11_MAPPED_SUBRESOURCE constantbufferMSR;

        DeviceContext->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &constantbufferMSR);
        FConstants* constants = (FConstants*)constantbufferMSR.pData;
        {
            constants->Offset = Offset;
        }

        DeviceContext->Unmap(ConstantBuffer, 0);
    }
}


void URenderer::Release()
{
    RasterizerState->Release();

    // 렌더 타겟을 초기화
    DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

    ReleaseFrameBuffer();
    ReleaseDeviceAndSwapChain();
}

void URenderer::ReleaseDeviceAndSwapChain()
{
    if (DeviceContext)
    {
        DeviceContext->Flush(); // 남아있는 GPU 명령 실행
    }

    if (SwapChain)
    {
        SwapChain->Release();
        SwapChain = nullptr;
    }

    if (Device)
    {
        Device->Release();
        Device = nullptr;
    }

    if (DeviceContext)
    {
        DeviceContext->Release();
        DeviceContext = nullptr;
    }
}

void URenderer::ReleaseFrameBuffer()
{
    if (FrameBuffer)
    {
        FrameBuffer->Release();
        FrameBuffer = nullptr;
    }

    if (FrameBufferRTV)
    {
        FrameBufferRTV->Release();
        FrameBufferRTV = nullptr;
    }
}

void URenderer::ReleaseRasterizerState()
{
    if (RasterizerState)
    {
        RasterizerState->Release();
        RasterizerState = nullptr;
    }
}

void URenderer::ReleaseShader()
{
    if (SimpleInputLayout)
    {
        SimpleInputLayout->Release();
        SimpleInputLayout = nullptr;
    }

    if (SimplePixelShader)
    {
        SimplePixelShader->Release();
        SimplePixelShader = nullptr;
    }

    if (SimpleVertexShader)
    {
        SimpleVertexShader->Release();
        SimpleVertexShader = nullptr;
    }

}

void URenderer::ReleaseVertexBuffer(ID3D11Buffer* vertexBuffer)
{
    vertexBuffer->Release();
}

void URenderer::ReleaseConstantBuffer()
{
    if (ConstantBuffer)
    {
        ConstantBuffer->Release();
        ConstantBuffer = nullptr;
    }
}

