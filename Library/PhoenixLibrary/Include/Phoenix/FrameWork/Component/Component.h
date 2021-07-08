#pragma once

#include <memory>
#include "Phoenix/Math/PhoenixMath.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class Actor;
		class Component
		{
		public:
			std::weak_ptr<Actor> owner;

		public:
			Component() {}
			virtual ~Component() {}

		public:
			// 生成時に一度だけ呼ばれる
			virtual void Awake() {}

			// 初期化
			virtual void Start() {}

			// 更新
			virtual void Update(Phoenix::f32 elapsedTime) {}

		public:
			// オーナー設定
			void SetOwner(std::shared_ptr<Actor> actor) { owner = actor; }

			// オーナー取得
			std::shared_ptr<Actor> GetOwner() { return owner.lock(); }
		};
	}
}