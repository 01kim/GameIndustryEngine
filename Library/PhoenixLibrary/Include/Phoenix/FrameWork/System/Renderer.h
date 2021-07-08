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
			// �R���X�g���N�^
			void Construct() override;

			// �f�X�g���N�^
			void Destruct() override;

			// ������
			void Initialize() override;

			// �I����
			void Finalize() override;

			// �X�V
			void Update(Phoenix::f32 elapsedTime) override;

			// �`��
			void Draw(Phoenix::f32 elapsedTime) override;
		};
	}
}