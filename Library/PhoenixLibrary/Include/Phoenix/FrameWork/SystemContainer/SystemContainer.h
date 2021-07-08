#pragma once

#include <memory>
#include <list>
#include "Phoenix/Math/PhoenixMath.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class ISystem;
		class SystemContainer : public std::enable_shared_from_this<SystemContainer>
		{
		private:
			std::list<std::shared_ptr<ISystem>> systems;

		public:
			SystemContainer() {}
			~SystemContainer() {}

		public:
			// ����
			static std::shared_ptr<SystemContainer> Create();

			// �R���X�g���N�^
			void Construct();

			// ������
			void Initialize();

			// �I����
			void Finalize();

			// �X�V
			void Update(Phoenix::f32 elapsedTime);

			// �`��
			void Draw(Phoenix::f32 elapsedTime);

		private:
			// �V�X�e���̒ǉ�
			void AddSystem(std::shared_ptr<ISystem> system);

		public:
			// �V�X�e���̎擾
			template<class T>
			std::shared_ptr<T> GetSystem()
			{
				for (auto system : systems)
				{
					std::shared_ptr<T> buff = std::dynamic_pointer_cast<T>(system);
					if (buff != nullptr)
					{
						return buff;
					}
				}

				return nullptr;
			}

			// �V�X�e���̒ǉ�
			template<class T>
			std::shared_ptr<T> AddSystem()
			{
				std::shared_ptr<T> buff = std::make_shared<T>();
				AddSystem(buff);

				return buff;
			}
		};
	}
}