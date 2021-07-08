#pragma once
#include "Phoenix/FrameWork/System/System.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class Actor;
		class ActorSystem : public ISystem
		{
		private:
			std::vector<std::shared_ptr<Actor>> actors;

		public:
			ActorSystem() {}
			~ActorSystem() override {}

		public:
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

			// アクターをクリア
			void ClearActors();

		private:
			// アクターを追加
			void AddActor(std::shared_ptr<Actor> actor);

		public:
			// アクター達を取得
			std::vector<std::shared_ptr<Actor>> GetActors() const;

			// アクターを取得
			template<class T>
			std::shared_ptr<Actor> GetActor() const
			{
				for (auto actor : actors)
				{
					std::shared_ptr<T> buff = std::dynamic_pointer_cast<std::shared_ptr<T>>(actor);
					if (buff != nullptr)
					{
						return buff;
					}
				}
				return nullptr;
			}

			// アクターを追加
			template<class T>
			std::shared_ptr<T> AddActor()
			{
				std::shared_ptr<T> actor = std::make_shared<T>();
				AddActor(actor);

				return actor;
			}
		};
	}
}