#include <windows.h>

// D3D ��뿡 �ʿ��� ���̺귯������ ��ũ�մϴ�.
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// D3D ��뿡 �ʿ��� ������ϵ��� �����մϴ�.
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

// ���� �޽����� ó���� �Լ�
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
	// ������ Ŭ���� �̸�
	WCHAR WindowClass[] = L"JungleWindowClass";

	// ������ Ÿ��Ʋ�ٿ� ǥ�õ� �̸�
	WCHAR Title[] = L"Game Tech Lab";

	// ���� �޽����� ó���� �Լ��� WndProc�� �Լ� �����͸� WindowClass ����ü�� �ִ´�.
	WNDCLASSW wndclass = { 0, WndProc, 0, 0, 0, 0, 0, 0, 0, WindowClass };

	// ������ Ŭ���� ���
	RegisterClassW(&wndclass);

	// 1024 x 1024 ũ�⿡ ������ ����
	HWND hWnd = CreateWindowExW(0, WindowClass, Title, WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 1024,
		nullptr, nullptr, hInstance, nullptr);

	bool bIsExit = false;

	// ���� �����ϴ� �ڵ带 ���⿡ �߰��մϴ�.

	// Renderer Class�� �����մϴ�.
	URenderer	renderer;

	// D3D11 �����ϴ� �Լ��� ȣ���մϴ�.
	renderer.Create(hWnd);
	// ������ ���� ���Ŀ� ���̴��� �����ϴ� �Լ��� ȣ���մϴ�.
	renderer.CreateShader();
	renderer.CreateConstantBuffer();

	// ImGui �ʱ�ȭ
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init((void*)hWnd);
	ImGui_ImplDX11_Init(renderer.Device, renderer.DeviceContext);

	// Renderer�� Shader ���� ���Ŀ� ���ؽ� ���۸� ����
	
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

	// ����
	
	ETypePrimitive typePrimitive = ETypePrimitive::EPT_Triangle;

	FVector offset(0.0f);

	// Main Loop (Quit Message�� ������ ������ �Ʒ� Loop�� ������ �����ϰ� ��)
	while (bIsExit == false)
	{
		MSG msg;

		// ó���� �޽����� �� �̻� ������ ���� ����
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// Ű �Է� �޽����� ����
			TranslateMessage(&msg);

			// �޽����� ������ ������ ���ν����� ����, �޽����� ������ ����� WndProc ���� ���޵�
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				bIsExit = true;
				break;
			}
			else if (msg.message == WM_KEYDOWN) // Ű���� ������ ��
			{
				// ���� Ű�� ����Ű��� �ش� ���⿡ ���缭
				// offset ������ x, y �ɹ� ������ ���� �����մϴ�.
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
		// �Ź� ����Ǵ� �ڵ带 ���⿡ �߰��մϴ�.

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

		// ���� ImGui UI ��Ʈ�� �߰��� ImGui::NewFrame()�� ImGui::Render() ������ ���⿡ ��ġ�մϴ�.

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

	// �Ҹ��ϴ� �ڵ带 ���⿡ �߰��մϴ�.
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
