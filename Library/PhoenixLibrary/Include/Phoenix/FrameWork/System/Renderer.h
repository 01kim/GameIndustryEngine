#pragma once
#include "System.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class Renderer : public Phoenix::FrameWork::ISystem
		{
		private:


		public:
			Renderer() {}
			~Renderer() override {}

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

			// 描画
			void Draw(Phoenix::f32 elapsedTime) override;
		};
	}
}