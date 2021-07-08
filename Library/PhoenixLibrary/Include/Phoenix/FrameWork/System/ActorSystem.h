#pragma once
#include "Phoenix/FrameWork/System/System.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class Actor;
		class ActorSystem : public ISystem
		{
		private:
			std::vector<std::shared_ptr<Actor>> actors;

		public:
			ActorSystem() {}
			~ActorSystem() override {}

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

			// �A�N�^�[���N���A
			void ClearActors();

		private:
			// �A�N�^�[��ǉ�
			void AddActor(std::shared_ptr<Actor> actor);

		public:
			// �A�N�^�[�B���擾
			std::vector<std::shared_ptr<Actor>> GetActors() const;

			// �A�N�^�[���擾
			template<class T>
			std::shared_ptr<Actor> GetActor() const
			{
				for (auto actor : actors)
				{
					std::shared_ptr<T> buff = std::dynamic_pointer_cast<std::shared_ptr<T>>(actor);
					if (buff != nullptr)
					{
						return buff;
					}
				}
				return nullptr;
			}

			// �A�N�^�[��ǉ�
			template<class T>
			std::shared_ptr<T> AddActor()
			{
				std::shared_ptr<T> actor = std::make_shared<T>();
				AddActor(actor);

				return actor;
			}
		};
	}
}