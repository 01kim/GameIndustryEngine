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
			// �R���X�g���N�^
			virtual void Construct() = 0;

			// �f�X�g���N�^
			virtual void Destruct() = 0;

			// ������
			virtual void Initialize() = 0;

			// �I����
			virtual void Finalize() = 0;

			// �X�V
			virtual void Update(Phoenix::f32 elapsedTime) = 0;

			// �`��
			virtual void Draw(Phoenix::f32 elapsedTime) {}

		public:
			// �e�|�C���^�[�ݒ�
			void SetParent(std::shared_ptr<SystemContainer> parent)
			{
				this->parent = parent;
			}
		};
	}
}