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
			// アクターを管理する配列を初期化
			actorSystem->ClearActors();

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

		// アクター管理クラスを設定
		void IScene::SetActorSystem(std::shared_ptr<ActorSystem> actorSystem)
		{
			this->actorSystem = actorSystem;
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

		// アクター管理クラスを設定
		void SceneSystem::SetActorSystem(std::shared_ptr<ActorSystem> actorSystem)
		{
			this->actorSystem = actorSystem;
		}

		// シーンを追加
		void SceneSystem::AddScene(std::shared_ptr<IScene> scene)
		{
			scene->Construct();
			scene->SetActorSystem(actorSystem);
			scenes.emplace_back(scene);
		}
	}
}