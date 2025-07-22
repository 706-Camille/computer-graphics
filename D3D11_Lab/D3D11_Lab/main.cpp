#include <windows.h>

// D3D 사용에 필요한 라이브러리들을 링크합니다.
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// D3D 사용에 필요한 헤더파일들을 포함합니다.
#include <d3d11.h>
#include <d3dcompiler.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "imGui/imgui_impl_win32.h"

#include "Renderer.h"
#include "Types.h"
#include "Geometry.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 각종 메시지를 처리할 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return true;
	}

	switch (message)
	{
	case WM_DESTROY:
		// Signal that the app should quit
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// 윈도우 클래스 이름
	WCHAR WindowClass[] = L"JungleWindowClass";

	// 윈도우 타이틀바에 표시될 이름
	WCHAR Title[] = L"Game Tech Lab";

	// 각종 메시지를 처리할 함수인 WndProc의 함수 포인터를 WindowClass 구조체에 넣는다.
	WNDCLASSW wndclass = { 0, WndProc, 0, 0, 0, 0, 0, 0, 0, WindowClass };

	// 윈도우 클래스 등록
	RegisterClassW(&wndclass);

	// 1024 x 1024 크기에 윈도우 생성
	HWND hWnd = CreateWindowExW(0, WindowClass, Title, WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 1024,
		nullptr, nullptr, hInstance, nullptr);

	bool bIsExit = false;

	// 각종 생성하는 코드를 여기에 추가합니다.

	// Renderer Class를 생성합니다.
	URenderer	renderer;

	// D3D11 생성하는 함수를 호출합니다.
	renderer.Create(hWnd);
	// 렌더러 생성 직후에 쉐이더를 생성하는 함수를 호출합니다.
	renderer.CreateShader();
	renderer.CreateConstantBuffer();

	// ImGui 초기화
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init((void*)hWnd);
	ImGui_ImplDX11_Init(renderer.Device, renderer.DeviceContext);

	// Renderer와 Shader 생성 이후에 버텍스 버퍼를 생성
	
	UINT byteWidthTriangle = sizeof(FVertexSimple) * Geometry::triangle_vertex_count;
	UINT byteWidthCube = sizeof(FVertexSimple) * Geometry::cube_vertex_count;
	UINT byteWidthSphere = sizeof(FVertexSimple) * Geometry::sphere_vertex_count;

	float scaleMod = 0.1f;
	for (UINT i = 0; i < Geometry::sphere_vertex_count; i++)
	{
		Geometry::sphere_vertices[i].x *= scaleMod;
		Geometry::sphere_vertices[i].y *= scaleMod;
		Geometry::sphere_vertices[i].z *= scaleMod;
	}
	
	ID3D11Buffer* vertexBufferTriangle =  renderer.CreateVertexBuffer(Geometry::triangle_vertices, byteWidthTriangle);
	ID3D11Buffer* vertexBufferCube = renderer.CreateVertexBuffer(Geometry::cube_vertices, byteWidthCube);
	ID3D11Buffer* vertexBufferSphere = renderer.CreateVertexBuffer(Geometry::sphere_vertices, byteWidthSphere);

	// 생성
	
	ETypePrimitive typePrimitive = ETypePrimitive::EPT_Triangle;

	FVector offset(0.0f);

	// Main Loop (Quit Message가 들어오기 전까지 아래 Loop를 무한히 실행하게 됨)
	while (bIsExit == false)
	{
		MSG msg;

		// 처리할 메시지가 더 이상 없을때 까지 수행
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 키 입력 메시지를 번역
			TranslateMessage(&msg);

			// 메시지를 적절한 윈도우 프로시저에 전달, 메시지가 위에서 등록한 WndProc 으로 전달됨
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				bIsExit = true;
				break;
			}
			else if (msg.message == WM_KEYDOWN) // 키보드 눌렸을 때
			{
				// 눌린 키가 방향키라면 해당 방향에 맞춰서
				// offset 변수의 x, y 맴버 변수의 값을 조정합니다.
				if (msg.wParam == VK_LEFT)
				{
					offset.x -= 0.01f;
				}
				if (msg.wParam == VK_RIGHT)
				{
					offset.x += 0.01f;
				}
				if (msg.wParam == VK_UP)
				{
					offset.y += 0.01f;
				}
				if (msg.wParam == VK_DOWN)
				{
					offset.y -= 0.01f;
				}
			}
		}

		////////////////////////////////////////////
		// 매번 실행되는 코드를 여기에 추가합니다.

		renderer.Prepare();
		renderer.PrepareShader();

		renderer.UpdateConstant(offset);

		switch (typePrimitive)
		{
		case EPT_Triangle:
			renderer.RenderPrimitive(vertexBufferTriangle, Geometry::triangle_vertex_count);
			break;
		case EPT_Cube:
			renderer.RenderPrimitive(vertexBufferCube, Geometry::cube_vertex_count);
			break;
		case EPT_Sphere:
			renderer.RenderPrimitive(vertexBufferSphere, Geometry::sphere_vertex_count);
			break;
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// 이후 ImGui UI 컨트롤 추가는 ImGui::NewFrame()과 ImGui::Render() 사이인 여기에 위치합니다.

		ImGui::Begin("Jungle Property Window");

		ImGui::Text("Hello Jungle World");

		if (ImGui::Button("Change Primitive"))
		{
			switch (typePrimitive)
			{
			case EPT_Triangle:
				typePrimitive = EPT_Cube;
				break;
			case EPT_Cube:
				typePrimitive = EPT_Sphere;
				break;
			case EPT_Sphere:
				typePrimitive = EPT_Triangle;
				break;
			}
		}
		ImGui::End();
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		renderer.SwapBuffer();

		////////////////////////////////////////////
	}

	// 소멸하는 코드를 여기에 추가합니다.
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	renderer.ReleaseVertexBuffer(vertexBufferTriangle);
	renderer.ReleaseVertexBuffer(vertexBufferCube);
	renderer.ReleaseVertexBuffer(vertexBufferSphere);

	renderer.ReleaseConstantBuffer();
	renderer.ReleaseShader();
	renderer.Release();
	

	return 0;
}
