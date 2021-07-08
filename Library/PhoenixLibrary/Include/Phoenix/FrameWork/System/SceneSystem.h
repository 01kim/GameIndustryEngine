#pragma once

#include <map>
#include "Phoenix/Math/PhoenixMath.h"
#include "Phoenix/FrameWork/System/System.h"
#include "Phoenix/FrameWork/System/ActorSystem.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class IScene
		{
		protected:
			// アクター管理（プレイヤー、エネミー、ステージ etc...）
			std::shared_ptr<ActorSystem> actorSystem;

		public:
			IScene() {}
			virtual ~IScene() {}

		public:
			// コンストラクタ
			void Construct();
			virtual void DoConstruct() = 0;

			// デストラクタ
			void Destruct();
			virtual void DoDestruct() = 0;

			// 初期化
			void Initialize();
			virtual void DoInitialize() = 0;

			// 終了化
			void Finalize();
			virtual void DoFinalize() = 0;

			// 更新
			void Update(Phoenix::f32 elapsedTime);
			virtual void DoUpdate(Phoenix::f32 elapsedTime) = 0;

			// 描画
			void Draw(Phoenix::f32 elapsedTime);

			// アクター管理クラスを設定
			void SetActorSystem(std::shared_ptr<ActorSystem> actorSystem);
		};

		class SceneSystem : public ISystem
		{
		private:
			std::vector<std::shared_ptr<IScene>> scenes;
			std::shared_ptr<IScene> currentScene;
			std::shared_ptr<IScene> nextScene;

		private:
			// アクター管理（プレイヤー、エネミー、ステージ etc...）
			std::shared_ptr<ActorSystem> actorSystem;

		public:
			SceneSystem() {}
			~SceneSystem() override {}

		public:
			// 生成
			static std::shared_ptr<SceneSystem> Create();

			// コンストラクタ
			void Construct() override;

			// デストラクタ
			void Destruct() override;

			// 初期化
			void Initialize() override;

			// 終了化
			void Finalize() override;

			// 更新
			void Update(Phoenix::f32 elapsedTime) override;

			// 描画
			void Draw(Phoenix::f32 elapsedTime);

			// アクター管理クラスを設定
			void SetActorSystem(std::shared_ptr<ActorSystem> actorSystem);

		private:
			// シーンを追加
			void AddScene(std::shared_ptr<IScene> scene);

		public:
			// シーンを所得
			template<class T>
			std::shared_ptr<T> GetScene()
			{
				for (auto scene : scenes)
				{
					std::shared_ptr<T> buff = std::dynamic_pointer_cast<std::shared_ptr<T>>(scene);
					if (buff != nullptr)
					{
						return buff;
					}
				}
				return nullptr;
			}

			// シーンを追加
			template<class T>
			std::shared_ptr<T> AddScene()
			{
				std::shared_ptr<T> scene = std::make_shared<T>();
				AddScene(scene);

				return scene;
			}

			// シーンを削除
			template<class T>
			void RemoveScene()
			{
				Phoenix::s32 cnt = 0;
				for (auto scene : scenes)
				{
					std::shared_ptr<T> buff = std::dynamic_pointer_cast<std::shared_ptr<T>>(scene);
					if (buff != nullptr)
					{
						break;
					}
					++cnt;
				}

				scenes.erase(scenes.begin() + cnt);
			}

			//	シーンの切り替え
			template<class T>
			void ChangeScene()
			{
				std::shared_ptr<T> scene = GetScene<T>();
				if (scene != nullptr)
				{
					nextScene = scene;
				}
			}
		};
	}
}