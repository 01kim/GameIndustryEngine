#include "pch.h"
#include "Phoenix/FrameWork/Actor/Actor.h"
#include "Phoenix/FrameWork/Component/Component.h"
#include "Phoenix/FrameWork/Component/Transform.h"


namespace Phoenix
{
	namespace FrameWork
	{
		// 生成
		/*std::shared_ptr<Actor> Actor::Create()
		{
			return std::make_shared<Actor>();
		}*/

		// コンストラクタ
		void Actor::Construct()
		{
			AddComponent<Transform>();
			DoConstruct();
		}

		// デストラクタ
		void Actor::Destruct()
		{
			DoDestruct();
		}

		// 初期化
		void Actor::Initialize()
		{
			for (auto child : children)
			{
				child->Initialize();
			}

			for (auto component : components)
			{
				//component->Initialize();
			}

			DoInitialize();
		}

		// 終了化
		void Actor::Finalize()
		{
			for (auto child : children)
			{
				child->Finalize();
			}

			for (auto component : components)
			{
				//component->Finalize();
			}

			DoFinalize();
		}

		// 更新
		void Actor::Update(Phoenix::f32 elapsedTime)
		{
			for (auto child : children)
			{
				child->Update(elapsedTime);
			}

			for (auto component : components)
			{
				component->Update(elapsedTime);
			}

			DoUpdate(elapsedTime);
		}

		// 描画
		//void Actor::Draw(Phoenix::f32 elapsedTime)
		//{
		//	for (auto child : children)
		//	{
		//		child->Draw(elapsedTime);
		//	}

		//	/*for (auto component : components)
		//	{
		//		component->Draw();
		//	}*/
		//}

		// 親アクターの設定
		void Actor::SetParentActor(std::shared_ptr<Actor> actor)
		{
			parent = actor;
		}

		// アクターを追加
		void Actor::AddChildActor(std::shared_ptr<Actor> actor)
		{
			actor->SetParentActor(shared_from_this());
			actor->Construct();

			children.emplace_back(actor);
		}

		// アクターを削除
		void Actor::RemoveChildActor(std::shared_ptr<Actor> actor)
		{
			actor->SetParentActor(nullptr);
			actor->Destruct();

			auto&& it = std::find(children.begin(), children.end(), actor);
			if (it != children.end())
			{
				children.erase(it);
			}
		}

		// コンポーネントを追加
		void Actor::AddComponent(std::shared_ptr<Component> component)
		{
			component->SetOwner(shared_from_this());
			component->Awake();

			components.emplace_back(component);
		}

		// コンポーネントを削除
		void Actor::RemoveComponent(std::shared_ptr<Component> component)
		{
			component->SetOwner(nullptr);
			//component->Destruct();

			auto&& it = std::find(components.begin(), components.end(), component);
			if (it != components.end())
			{
				components.erase(it);
			}
		}
	}
}