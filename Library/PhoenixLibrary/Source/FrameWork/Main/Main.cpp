#include "pch.h"
#include "Phoenix/FrameWork/Main.h"
#include "../../ExternalLibrary/ImGui/Include/imgui.h"
#include "../../ExternalLibrary/ImGui/Include/imgui_impl_win32.h"
#include "../../ExternalLibrary/ImGui/Include/imgui_impl_dx11.h"
#include "../../ExternalLibrary/ImGui/Include/imgui_internal.h"
#include "../Source/Graphics/Device/Win/DirectX11/DeviceDX11.h"
#include "../Source/Graphics/Context/Win/DirectX11/ContextDX11.h"
#include "Phoenix/FrameWork/Input/InputDevice.h"
#include "Phoenix/FrameWork/System/SceneSystem.h"
#include "Phoenix/FrameWork/System/ActorSystem.h"
#include "Phoenix/FrameWork/System/Renderer.h"


namespace Phoenix
{
	namespace FrameWork
	{
		//****************************************************************************
		// メインループ
		//****************************************************************************
		bool Main::Initialize(uintPtr instance)
		{
#if (defined(DEBUG) | defined(_DEBUG))
			Phoenix::s32 width = 1280;
			Phoenix::s32 height = 720;
#else
			Phoenix::s32 width = 1920;
			Phoenix::s32 height = 1080;
#endif
			display = Phoenix::OS::IDisplay::Create();

			if (!display->Initialize(L"BOXER", width, height, instance))
			{
				return false;
			}

			graphicsDevice = Phoenix::Graphics::IGraphicsDevice::Create();
			if (!graphicsDevice->Initialize(display.get()))
			{
				return false;
			}

			Phoenix::Graphics::Viewport v;
			v.x = 0.0f;
			v.y = 0.0f;
			v.width = static_cast<Phoenix::f32>(width);
			v.height = static_cast<Phoenix::f32>(height);
			v.minDepth = 0.0f;
			v.maxDepth = 1.0f;
			graphicsDevice->GetContext()->SetViewports(1, &v);

			ID3D11Device* d3dDevice = static_cast<Graphics::DeviceDX11*>(graphicsDevice->GetDevice())->GetD3DDevice();
			ID3D11DeviceContext* d3dDeviceContext = static_cast<Graphics::DeviceDX11*>(graphicsDevice->GetDevice())->GetD3DContext();

			ImGui::SetCurrentContext(ImGui::CreateContext());
			ImGui_ImplWin32_Init(display->GetHWND());
			ImGui_ImplDX11_Init(d3dDevice, d3dDeviceContext);

			ImGui::StyleColorsLight();

			ImGui::GetStyle().WindowRounding = 1.0f;
			ImGui::GetStyle().FrameRounding = 1.0f;
			ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
			ImGui::GetStyle().Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
			ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 0.85f);
			ImGui::GetStyle().Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
			ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

			ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
			ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = ImVec4(0.57f, 0.57f, 0.57f, 1.00f);

			ImGui::GetStyle().Colors[ImGuiCol_Tab] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
			ImGui::GetStyle().Colors[ImGuiCol_TabActive] = ImVec4(0.57f, 0.57f, 0.57f, 1.00f);


			ImGuiIO& io = ImGui::GetIO();
#if	!defined(PHOENIX_TARGET_DEBUG)
			io.IniFilename = NULL;
#endif
			io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 20.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
			//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, NULL, glyphRangesJapanese);
			//io.Fonts->AddFontFromFileTTF(".\\consolab.ttf", 10.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
			//io.Fonts->AddFontFromFileTTF(".\\Inconsolata-Bold.ttf", 12.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
			
			// システム追加
			systemContainer = SystemContainer::Create();
			{
				systemContainer->AddSystem<SceneSystem>();
				systemContainer->AddSystem<ActorSystem>();
				systemContainer->AddSystem<Renderer>();
			}
			systemContainer->Construct();
			systemContainer->Initialize();

			elapsedTime = 0.0f;

			DoInitialize();

			return true;
		}

		void Main::Finalize()
		{
			systemContainer->Finalize();

			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();

			graphicsDevice->Finalize();
			display->Finalize();
		}

		void Main::Run()
		{
			// 更新
			{
				display->TimerTick();
				display->CalculateFrameStats();
				elapsedTime = display->TimerInterval() * 60.0f;

				GetXInputState(&xInput[0], 0, elapsedTime);
				GetDInputState(&dInput[0], 0, elapsedTime);

				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();

				systemContainer->Update(elapsedTime);
			}

			// 描画
			{
				graphicsDevice->RenderBegin();
				systemContainer->Draw(elapsedTime);
				graphicsDevice->RenderEnd();

				ImGui::Render();
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
				
				graphicsDevice->Present(0);
			}
		}
	}
}