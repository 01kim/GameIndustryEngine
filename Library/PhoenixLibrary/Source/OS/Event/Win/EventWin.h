#pragma once

#include <Windows.h>
#include "Phoenix/OS/Event.h"


namespace Phoenix
{
	namespace OS
	{
		//****************************************************************************
		// Windows版イベント操作クラス
		//****************************************************************************
		class EventWIN final : public IEvent
		{
		private:
			HANDLE handle = nullptr;

		public:
			~EventWIN() override { Finalize(); }

		public:
			// 初期化
			bool Initialize(bool manual = false) override;

			// 終了化
			void Finalize() override;

			// シグナル設定
			void Set() override;

			// シグナル解除
			void Reset() override;

			// シグナル設定待ち
			void Wait(f32 time = 0.0f) override;
		};
	}
}