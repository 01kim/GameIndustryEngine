#include "pch.h"
#include "Phoenix/FrameWork/SystemContainer/SystemContainer.h"
#include "Phoenix/FrameWork/System/System.h"


namespace Phoenix
{
	namespace FrameWork
	{
		// 生成
		std::shared_ptr<SystemContainer> SystemContainer::Create()
		{
			return std::make_shared<SystemContainer>();
		}

		// コンストラクタ
		void SystemContainer::Construct()
		{
			for (auto system : systems)
			{
				system->Construct();
			}
		}

		// 初期化
		void SystemContainer::Initialize()
		{
			for (auto system : systems)
			{
				system->Initialize();
			}
		}

		// 終了化
		void SystemContainer::Finalize()
		{
			for (auto system : systems)
			{
				system->Finalize();
			}
		}

		// 更新
		void SystemContainer::Update(Phoenix::f32 elapsedTime)
		{
			for (auto system : systems)
			{
				system->Update(elapsedTime);
			}
		}

		// 描画
		void SystemContainer::Draw(Phoenix::f32 elapsedTime)
		{
			for (auto system : systems)
			{
				system->Draw(elapsedTime);
			}
		}

		// システムの追加
		void SystemContainer::AddSystem(std::shared_ptr<ISystem> system)
		{
			system->SetParent(shared_from_this());
			systems.push_back(system);
		}
	}
}