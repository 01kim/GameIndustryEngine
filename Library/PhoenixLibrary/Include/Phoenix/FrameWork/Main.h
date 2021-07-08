#pragma once

#include <memory>
#include <string>
#include "Phoenix/OS/Main.h"
#include "Phoenix/OS/Display.h"
#include "Phoenix/Graphics/GraphicsDevice.h"
#include "Phoenix/FrameWork/SystemContainer/SystemContainer.h"


namespace Phoenix
{
	namespace FrameWork
	{
		//****************************************************************************
		// メインループ
		//****************************************************************************
		class Main : public OS::IMain
		{
		protected:
			std::unique_ptr<OS::IDisplay> display;
			std::shared_ptr<Graphics::IGraphicsDevice> graphicsDevice;
			std::shared_ptr<SystemContainer> systemContainer;
			float elapsedTime = 0.0f;

		public:
			Main() {}
			~Main() {}

		public:
			// 初期化
			bool Initialize(uintPtr instance) override;

			// 終了化
			void Finalize() override;

			// 実行
			void Run() override;

		protected:
			// 初期化
			virtual bool DoInitialize() = 0;
		};
	} // namespace FrameWork
} // namespace Phoenix