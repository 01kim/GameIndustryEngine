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
		// ���C�����[�v
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
			// ������
			bool Initialize(uintPtr instance) override;

			// �I����
			void Finalize() override;

			// ���s
			void Run() override;

		protected:
			// ������
			virtual bool DoInitialize() = 0;
		};
	} // namespace FrameWork
} // namespace Phoenix