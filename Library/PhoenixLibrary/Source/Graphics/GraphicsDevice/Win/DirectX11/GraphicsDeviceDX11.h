#pragma once

#include "Phoenix/Graphics/GraphicsDevice.h"


namespace Phoenix
{
	namespace Graphics
	{
		//****************************************************************************
		// DirectX11版グラフィックスデバイス操作オブジェクト
		//****************************************************************************
		class GraphicsDeviceDX11 final : public IGraphicsDevice
		{
		private:
			std::unique_ptr<IDevice> device;
			std::unique_ptr<IContext> context;
			std::unique_ptr<ISwapChain> swapChain;

		public:
			// 初期化
			bool Initialize(OS::IDisplay* display) override;

			// 終了化
			void Finalize() override;

		public:
			IDevice* GetDevice() override { return device.get(); }
			IContext* GetContext() override { return context.get(); }
			ISwapChain* GetSwapChain() override { return swapChain.get(); }

			// レンダリングされたイメージを表示
			void Present(int syncInterval);

			// 描画開始
			void RenderBegin();

			// 描画終了
			void RenderEnd();
		};
	} // namespace Graphics
} // namespace Phoenix