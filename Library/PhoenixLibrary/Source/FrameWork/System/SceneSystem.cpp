#include "pch.h"
#include "Phoenix/FrameWork/System/SceneSystem.h"


namespace Phoenix
{
	namespace FrameWork
	{
		// コンストラクタ
		void IScene::Construct()
		{
			DoConstruct();
		}

		// デストラクタ
		void IScene::Destruct()
		{
			DoDestruct();
		}

		// 初期化
		void IScene::Initialize()
		{
			DoInitialize();
		}

		// 終了化
		void IScene::Finalize()
		{
			DoFinalize();
		}

		// 更新
		void IScene::Update(Phoenix::f32 elapsedTime)
		{
			DoUpdate(elapsedTime);
		}

		// 描画
		void IScene::Draw(Phoenix::f32 elapsedTime)
		{

		}

		// 生成
		std::shared_ptr<SceneSystem> SceneSystem::Create()
		{
			return std::make_shared<SceneSystem>();
		}

		// コンストラクタ
		void SceneSystem::Construct()
		{

		}

		// デストラクタ
		void SceneSystem::Destruct()
		{
			nextScene.reset();
			currentScene.reset();
			scenes.clear();
		}

		// 初期化
		void SceneSystem::Initialize()
		{

		}

		// 終了化
		void SceneSystem::Finalize()
		{
			nextScene.reset();
			currentScene.reset();
			scenes.clear();
		}

		// 更新
		void SceneSystem::Update(Phoenix::f32 elapsedTime)
		{
			if (!currentScene) return;

			if (nextScene)
			{
				currentScene = nextScene;
				currentScene->Initialize();
				nextScene.reset();
			}

			currentScene->Update(elapsedTime);
		}

		// 描画
		void SceneSystem::Draw(Phoenix::f32 elapsedTime)
		{
			if (!currentScene) return;
			currentScene->Draw(elapsedTime);
		}

		// シーンを追加
		void SceneSystem::AddScene(std::shared_ptr<IScene> scene)
		{
			scene->Construct();
			scenes.emplace_back(scene);
		}
	}
}