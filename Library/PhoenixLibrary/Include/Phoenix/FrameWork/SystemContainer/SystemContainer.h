#pragma once

#include <memory>
#include <list>
#include "Phoenix/Math/PhoenixMath.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class ISystem;
		class SystemContainer : public std::enable_shared_from_this<SystemContainer>
		{
		private:
			std::list<std::shared_ptr<ISystem>> systems;

		public:
			SystemContainer() {}
			~SystemContainer() {}

		public:
			// 生成
			static std::shared_ptr<SystemContainer> Create();

			// コンストラクタ
			void Construct();

			// 初期化
			void Initialize();

			// 終了化
			void Finalize();

			// 更新
			void Update(Phoenix::f32 elapsedTime);

			// 描画
			void Draw(Phoenix::f32 elapsedTime);

		private:
			// システムの追加
			void AddSystem(std::shared_ptr<ISystem> system);

		public:
			// システムの取得
			template<class T>
			std::shared_ptr<T> GetSystem()
			{
				for (auto system : systems)
				{
					std::shared_ptr<T> buff = std::dynamic_pointer_cast<T>(system);
					if (buff != nullptr)
					{
						return buff;
					}
				}

				return nullptr;
			}

			// システムの追加
			template<class T>
			std::shared_ptr<T> AddSystem()
			{
				std::shared_ptr<T> buff = std::make_shared<T>();
				AddSystem(buff);

				return buff;
			}
		};
	}
}