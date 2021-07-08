#pragma once

#include <memory>
#include <vector>
#include "Phoenix/Math/PhoenixMath.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class Component;
		class Actor : public std::enable_shared_from_this<Actor>
		{
		private:
			std::weak_ptr<Actor> parent;
			std::vector<std::shared_ptr<Actor>> children;
			std::vector<std::shared_ptr<Component>> components;

		public:
			Actor() {}
			virtual ~Actor() {}

		public:
			// ����
			//static std::shared_ptr<Actor> Create();

			// �R���X�g���N�^
			void Construct();
			virtual void DoConstruct() {}

			// �f�X�g���N�^
			void Destruct();
			virtual void DoDestruct() {}

			// ������
			void Initialize();
			virtual void DoInitialize() {}

			// �I����
			void Finalize();
			virtual void DoFinalize() {}

			// �X�V
			void Update(Phoenix::f32 elapsedTime);
			virtual void DoUpdate(Phoenix::f32 elapsedTime) {}

			// �`��
			//virtual void Draw(Phoenix::f32 elapsedTime);

			// �e�A�N�^�[�̐ݒ�
			void SetParentActor(std::shared_ptr<Actor> actor);

			// �A�N�^�[��ǉ�
			void AddChildActor(std::shared_ptr<Actor> actor);

			// �A�N�^�[���폜
			void RemoveChildActor(std::shared_ptr<Actor> actor);

			// �R���|�[�l���g��ǉ�
			void AddComponent(std::shared_ptr<Component> component);

			// �R���|�[�l���g���폜
			void RemoveComponent(std::shared_ptr<Component> component);

		public:
			template<class T>
			std::shared_ptr<T> GetChildActor()
			{
				for (auto component : components)
				{
					std::shared_ptr<T> obj = std::dynamic_pointer_cast<std::shared_ptr<T>>(component);
					if (obj != nullptr)
					{
						return obj;
					}
				}
				return nullptr;
			}

			template<class T>
			std::shared_ptr<T> AddChildActor()
			{
				std::shared_ptr<T> obj = std::make_shared<T>();
				AddChildActor(obj);

				return obj;
			}

		public:
			template<class T>
			std::shared_ptr<T> GetComponent()
			{
				for (auto component : components)
				{
					std::shared_ptr<T> obj = std::dynamic_pointer_cast<T>(component);
					if (obj != nullptr)
					{
						return obj;
					}
				}
				return nullptr;
			}

			template<class T>
			std::shared_ptr<T> AddComponent()
			{
				std::shared_ptr<T> obj = std::make_shared<T>();
				AddComponent(obj);

				return obj;
			}
		};
	}
}