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

		}

		// デストラクタ
		void ActorSystem::Destruct()
		{

		}

		// 初期化
		void ActorSystem::Initialize()
		{

		}

		// 終了化
		void ActorSystem::Finalize()
		{

		}

		// 更新
		void ActorSystem::Update(Phoenix::f32 elapsedTime)
		{

		}

		// アクター達を取得
		std::vector<std::shared_ptr<Actor>> ActorSystem::GetActors() const
		{
			return actors;
		}
	}
}