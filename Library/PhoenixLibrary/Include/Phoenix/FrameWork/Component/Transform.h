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
			// ������
			void Initialize()
			{
				translate = Math::Vector3::Zero;
				rotate = Math::Quaternion::Zero;
				scale = Math::Vector3::OneAll;
				worldTransform = Math::Matrix::One;
			}

			// �X�V
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

			// �ړ��l�̐ݒ�
			void SetTranslate(Math::Vector3 translate) { this->translate = translate; }

			// ��]�l�̐ݒ�
			void SetRotate(Math::Quaternion rotate) { this->rotate = rotate; }

			// �X�P�[���l�̐ݒ�
			void SetScale(Math::Vector3 scale) { this->scale = scale; }

			// �ړ��l�̎擾
			const Math::Vector3& GetTranslate() { return translate; }

			// ��]�l�̎擾
			const Math::Quaternion& GetRotate() { return rotate; }

			// �X�P�[���l�̎擾
			const Math::Vector3& GetScale() { return scale; }

			// ���[���h�s��̎擾
			const Math::Matrix& GetWorldTransform() { return worldTransform; }
		};
	}
}