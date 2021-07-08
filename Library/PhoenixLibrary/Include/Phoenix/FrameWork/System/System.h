#pragma once
#include "Phoenix/Math/PhoenixMath.h"
#include "Phoenix/FrameWork/SystemContainer/SystemContainer.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class ISystem
		{
		private:
			std::weak_ptr<SystemContainer> parent;

		public:
			ISystem() {}
			virtual ~ISystem() {}

		public:
			// コンストラクタ
			virtual void Construct() = 0;

			// デストラクタ
			virtual void Destruct() = 0;

			// 初期化
			virtual void Initialize() = 0;

			// 終了化
			virtual void Finalize() = 0;

			// 更新
			virtual void Update(Phoenix::f32 elapsedTime) = 0;

			// 描画
			virtual void Draw(Phoenix::f32 elapsedTime) {}

		public:
			// 親ポインター設定
			void SetParent(std::shared_ptr<SystemContainer> parent)
			{
				this->parent = parent;
			}
		};
	}
}