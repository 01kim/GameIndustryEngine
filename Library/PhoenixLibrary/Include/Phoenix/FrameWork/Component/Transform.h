#pragma once

#include "Component.h"
#include "Phoenix/Math/PhoenixMath.h"
#include "../../ExternalLibrary/ImGui/Include/imgui.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class Transform : public Component
		{
		private:
			Math::Vector3 translate = Math::Vector3::Zero;
			Math::Quaternion rotate = Math::Quaternion::Zero;
			Math::Vector3 scale = Math::Vector3::OneAll;
			Math::Matrix worldTransform = Math::Matrix::One;

		public:
			Transform() {}
			~Transform() override {}

		public:
			// 初期化
			void Initialize()
			{
				translate = Math::Vector3::Zero;
				rotate = Math::Quaternion::Zero;
				scale = Math::Vector3::OneAll;
				worldTransform = Math::Matrix::One;
			}

			// 更新
			void Update()
			{
				Phoenix::Math::Matrix S, R, T;
				S = Phoenix::Math::MatrixScaling(scale.x, scale.y, scale.z);
				R = Phoenix::Math::MatrixRotationQuaternion(&rotate);
				T = Phoenix::Math::MatrixTranslation(translate.x, translate.y, translate.z);

				worldTransform = S * R * T;
			}

			// GUI
			void GUI()
			{
				if (ImGui::TreeNode("Transform"))
				{
					ImGui::DragFloat3("pos", &translate.x);
					ImGui::DragFloat3("rotate", &rotate.x);
					ImGui::DragFloat3("scale", &scale.x);
					ImGui::TreePop();
				}
			}

			// 移動値の設定
			void SetTranslate(Math::Vector3 translate) { this->translate = translate; }

			// 回転値の設定
			void SetRotate(Math::Quaternion rotate) { this->rotate = rotate; }

			// スケール値の設定
			void SetScale(Math::Vector3 scale) { this->scale = scale; }

			// 移動値の取得
			const Math::Vector3& GetTranslate() { return translate; }

			// 回転値の取得
			const Math::Quaternion& GetRotate() { return rotate; }

			// スケール値の取得
			const Math::Vector3& GetScale() { return scale; }

			// ワールド行列の取得
			const Math::Matrix& GetWorldTransform() { return worldTransform; }
		};
	}
}