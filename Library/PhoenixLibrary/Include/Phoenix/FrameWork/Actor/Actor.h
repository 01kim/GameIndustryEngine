#pragma once

#include <memory>
#include <vector>
#include "Phoenix/Math/PhoenixMath.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class Component;
		class Actor : public std::enable_shared_from_this<Actor>
		{
		private:
			std::weak_ptr<Actor> parent;
			std::vector<std::shared_ptr<Actor>> children;
			std::vector<std::shared_ptr<Component>> components;

		public:
			Actor() {}
			virtual ~Actor() {}

		public:
			// 生成
			//static std::shared_ptr<Actor> Create();

			// コンストラクタ
			void Construct();
			virtual void DoConstruct() {}

			// デストラクタ
			void Destruct();
			virtual void DoDestruct() {}

			// 初期化
			void Initialize();
			virtual void DoInitialize() {}

			// 終了化
			void Finalize();
			virtual void DoFinalize() {}

			// 更新
			void Update(Phoenix::f32 elapsedTime);
			virtual void DoUpdate(Phoenix::f32 elapsedTime) {}

			// 描画
			//virtual void Draw(Phoenix::f32 elapsedTime);

			// 親アクターの設定
			void SetParentActor(std::shared_ptr<Actor> actor);

			// アクターを追加
			void AddChildActor(std::shared_ptr<Actor> actor);

			// アクターを削除
			void RemoveChildActor(std::shared_ptr<Actor> actor);

			// コンポーネントを追加
			void AddComponent(std::shared_ptr<Component> component);

			// コンポーネントを削除
			void RemoveComponent(std::shared_ptr<Component> component);

		public:
			template<class T>
			std::shared_ptr<T> GetChildActor()
			{
				for (auto component : components)
				{
					std::shared_ptr<T> obj = std::dynamic_pointer_cast<std::shared_ptr<T>>(component);
					if (obj != nullptr)
					{
						return obj;
					}
				}
				return nullptr;
			}

			template<class T>
			std::shared_ptr<T> AddChildActor()
			{
				std::shared_ptr<T> obj = std::make_shared<T>();
				AddChildActor(obj);

				return obj;
			}

		public:
			template<class T>
			std::shared_ptr<T> GetComponent()
			{
				for (auto component : components)
				{
					std::shared_ptr<T> obj = std::dynamic_pointer_cast<T>(component);
					if (obj != nullptr)
					{
						return obj;
					}
				}
				return nullptr;
			}

			template<class T>
			std::shared_ptr<T> AddComponent()
			{
				std::shared_ptr<T> obj = std::make_shared<T>();
				AddComponent(obj);

				return obj;
			}
		};
	}
}