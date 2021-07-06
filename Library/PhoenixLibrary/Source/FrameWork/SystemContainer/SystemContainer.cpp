#include "pch.h"
#include "Phoenix/FrameWork/SystemContainer/SystemContainer.h"
#include "Phoenix/FrameWork/System/System.h"


namespace Phoenix
{
	namespace FrameWork
	{
		// ����
		std::shared_ptr<SystemContainer> SystemContainer::Create()
		{
			return std::make_shared<SystemContainer>();
		}

		// �R���X�g���N�^
		void SystemContainer::Construct()
		{
			for (auto system : systems)
			{
				system->Construct();
			}
		}

		// ������
		void SystemContainer::Initialize()
		{
			for (auto system : systems)
			{
				system->Initialize();
			}
		}

		// �I����
		void SystemContainer::Finalize()
		{
			for (auto system : systems)
			{
				system->Finalize();
			}
		}

		// �X�V
		void SystemContainer::Update(Phoenix::f32 elapsedTime)
		{
			for (auto system : systems)
			{
				system->Update(elapsedTime);
			}
		}

		// �`��
		void SystemContainer::Draw(Phoenix::f32 elapsedTime)
		{
			for (auto system : systems)
			{
				system->Draw(elapsedTime);
			}
		}

		// �V�X�e���̒ǉ�
		void SystemContainer::AddSystem(std::shared_ptr<ISystem> system)
		{
			system->SetParent(shared_from_this());
			systems.push_back(system);
		}
	}
}