#include "Scene.h"
#include "SceneSystem.h"
#include "../../ExternalLibrary/ImGui/Include/imgui.h"
#include "../../ExternalLibrary/ImGui/Include/imgui_impl_win32.h"
#include "../../ExternalLibrary/ImGui/Include/imgui_impl_dx11.h"
#include "../../ExternalLibrary/ImGui/Include/imgui_internal.h"
#include "Phoenix/FrameWork/Input/InputDevice.h"
#include "Phoenix/Math/PhoenixMath.h"
#include "Phoenix/FrameWork/Shader/SkyMapShader.h"
#include "Phoenix/FND/Util.h"
#include "../Source/Graphics/Texture/Win/DirectX11/TextureDX11.h"
#include "../Source/Graphics/Context/Win/DirectX11/ContextDX11.h"
#include "../Enemy/Enemy.h"
#include "../AI/MetaAI/MetaType.h"
#include "Phoenix/OS/StartUp.h"
#include "../Easing/Easing.h"
#include "../AI/MetaAI/BattleEnemySystem.h"


void SceneGame::Construct(SceneSystem* sceneSystem)
{
	this->sceneSystem = sceneSystem;
	display = sceneSystem->GetDisplay();
	graphicsDevice = sceneSystem->GetGraphicsDevice();
	commonData = sceneSystem->GetSceneCommonData();
}

void SceneGame::Initialize()
{
}

void SceneGame::Update(Phoenix::f32 elapsedTime)
{
}

void SceneGame::Draw(Phoenix::f32 elapsedTime)
{
}

void SceneGame::GUI()
{
}