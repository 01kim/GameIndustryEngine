#include "pch.h"
#include "Phoenix/FrameWork/Actor/Actor.h"
#include "Phoenix/FrameWork/System/ActorSystem.h"


namespace Phoenix
{
	namespace FrameWork
	{
		// コンストラクタ
		void ActorSystem::Construct()
		{
			actors.clear();
		}

		// デストラクタ
		void ActorSystem::Destruct()
		{
			actors.clear();
		}

		// 初期化
		void ActorSystem::Initialize()
		{
			for (auto actor : actors)
			{
				actor->Initialize();
			}
		}

		// 終了化
		void ActorSystem::Finalize()
		{
			for (auto actor : actors)
			{
				actor->Finalize();
			}
			actors.clear();
		}

		// 更新
		void ActorSystem::Update(Phoenix::f32 elapsedTime)
		{
			for (auto actor : actors)
			{
				actor->Update(elapsedTime);
			}
		}

		// アクター達を取得
		std::vector<std::shared_ptr<Actor>> ActorSystem::GetActors() const
		{
			return actors;
		}

		// アクターをクリア
		void ActorSystem::ClearActors()
		{
			Finalize();
		}

		// アクターを追加
		void ActorSystem::AddActor(std::shared_ptr<Actor> actor)
		{
			actor->Construct();
			actors.emplace_back(actor);
		}
	}
}