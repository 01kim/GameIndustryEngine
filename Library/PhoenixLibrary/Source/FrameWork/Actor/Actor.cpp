#include "pch.h"
#include "Phoenix/FrameWork/Actor/Actor.h"
#include "Phoenix/FrameWork/Component/Component.h"
#include "Phoenix/FrameWork/Component/Transform.h"


namespace Phoenix
{
	namespace FrameWork
	{
		// ����
		/*std::shared_ptr<Actor> Actor::Create()
		{
			return std::make_shared<Actor>();
		}*/

		// �R���X�g���N�^
		void Actor::Construct()
		{
			AddComponent<Transform>();
			DoConstruct();
		}

		// �f�X�g���N�^
		void Actor::Destruct()
		{
			DoDestruct();
		}

		// ������
		void Actor::Initialize()
		{
			for (auto child : children)
			{
				child->Initialize();
			}

			for (auto component : components)
			{
				//component->Initialize();
			}

			DoInitialize();
		}

		// �I����
		void Actor::Finalize()
		{
			for (auto child : children)
			{
				child->Finalize();
			}

			for (auto component : components)
			{
				//component->Finalize();
			}

			DoFinalize();
		}

		// �X�V
		void Actor::Update(Phoenix::f32 elapsedTime)
		{
			for (auto child : children)
			{
				child->Update(elapsedTime);
			}

			for (auto component : components)
			{
				component->Update(elapsedTime);
			}

			DoUpdate(elapsedTime);
		}

		// �`��
		//void Actor::Draw(Phoenix::f32 elapsedTime)
		//{
		//	for (auto child : children)
		//	{
		//		child->Draw(elapsedTime);
		//	}

		//	/*for (auto component : components)
		//	{
		//		component->Draw();
		//	}*/
		//}

		// �e�A�N�^�[�̐ݒ�
		void Actor::SetParentActor(std::shared_ptr<Actor> actor)
		{
			parent = actor;
		}

		// �A�N�^�[��ǉ�
		void Actor::AddChildActor(std::shared_ptr<Actor> actor)
		{
			actor->SetParentActor(shared_from_this());
			actor->Construct();

			children.emplace_back(actor);
		}

		// �A�N�^�[���폜
		void Actor::RemoveChildActor(std::shared_ptr<Actor> actor)
		{
			actor->SetParentActor(nullptr);
			actor->Destruct();

			auto&& it = std::find(children.begin(), children.end(), actor);
			if (it != children.end())
			{
				children.erase(it);
			}
		}

		// �R���|�[�l���g��ǉ�
		void Actor::AddComponent(std::shared_ptr<Component> component)
		{
			component->SetOwner(shared_from_this());
			component->Awake();

			components.emplace_back(component);
		}

		// �R���|�[�l���g���폜
		void Actor::RemoveComponent(std::shared_ptr<Component> component)
		{
			component->SetOwner(nullptr);
			//component->Destruct();

			auto&& it = std::find(components.begin(), components.end(), component);
			if (it != components.end())
			{
				components.erase(it);
			}
		}
	}
}