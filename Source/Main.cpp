#include "Main.h"
#include "Phoenix/FND/Util.h"
#include "Phoenix/FND/STD.h"
#include "Phoenix/OS/Path.h"
#include "Phoenix/OS/ResourceManager.h"
#include "Phoenix/Graphics/Model.h"
#include "Phoenix/FrameWork/Renderer/ModelRenderer.h"
#include "Phoenix/FrameWork/Shader/BasicShader.h"
#include "Phoenix/FrameWork/Shader/BasicSkinShader.h"
#include "Phoenix/FrameWork/Shader/StandardShader.h"
#include "Player/Player.h"
#include "Scene/SceneTitle.h"


namespace Phoenix
{
	namespace OS
	{
		std::unique_ptr<IMain> IMain::Create()
		{
			return std::make_unique<Main>();
		}
	}
}

// 初期化
bool Main::DoInitialize()
{
	// シーン追加（タイトル、ゲーム、ゲームクリア、ゲームオーバー etc...）
	sceneSystem = systemContainer->GetSystem<Phoenix::FrameWork::SceneSystem>();
	sceneSystem->SetActorSystem(systemContainer->GetSystem<Phoenix::FrameWork::ActorSystem>());
	{
		sceneSystem->AddScene<SceneTitle>();
	}

	return true;
}