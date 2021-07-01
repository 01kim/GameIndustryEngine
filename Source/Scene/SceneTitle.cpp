#include "Scene.h"
#include "SceneSystem.h"
#include "../Source/Graphics/Context/Win/DirectX11/ContextDX11.h"
#include "../../ExternalLibrary/ImGui/Include/imgui.h"
#include "../../ExternalLibrary/ImGui/Include/imgui_impl_win32.h"
#include "../../ExternalLibrary/ImGui/Include/imgui_impl_dx11.h"
#include "../../ExternalLibrary/ImGui/Include/imgui_internal.h"
#include "Phoenix/FrameWork/Input/InputDevice.h"
#include "Phoenix/FND/Util.h"


void SceneTitle::Construct(SceneSystem* sceneSystem)
{
	this->sceneSystem = sceneSystem;
	display = sceneSystem->GetDisplay();
	graphicsDevice = sceneSystem->GetGraphicsDevice();
	commonData = sceneSystem->GetSceneCommonData();
}

void SceneTitle::Initialize()
{
}

void SceneTitle::Update(Phoenix::f32 elapsedTime)
{
}

void SceneTitle::Draw(Phoenix::f32 elapsedTime)
{
}

void SceneTitle::GUI()
{
}