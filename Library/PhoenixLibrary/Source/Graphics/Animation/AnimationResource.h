#pragma once

#include "Phoenix/Graphics/Animation.h"
#include "Phoenix/Math/PhoenixMath.h"


namespace Phoenix
{
	namespace Graphics
	{
		//****************************************************************************
		// アニメーションリソースクラス
		//****************************************************************************
		class AnimationResource : public IAnimationResource
		{
		private:
			AnimationData data;

		public:
			// アニメーションデータ取得
			const AnimationData& GetAnimationData() override { return data; }

			// 初期化
			bool Initialize(const char* filename);
		};

		//****************************************************************************
		// アニメーションリソースファクトリクラス
		//****************************************************************************
		class AnimationResourceFactory : public IAnimationResourceFactory
		{
		public:
			// リソース作成
			std::unique_ptr<OS::Resource> CreateResource(u32 type) override;

			// リソース読み込み
			bool LoadResource(OS::Resource* resource, OS::IFileStream* stream, const char* filename)  override;
		};
	} // namespace Graphics
} // namespace Phoenix