#include "pch.h"
#include "Phoenix/FrameWork/Actor/Actor.h"
#include "Phoenix/FrameWork/System/ActorSystem.h"


namespace Phoenix
{
	namespace FrameWork
	{
		// �R���X�g���N�^
		void ActorSystem::Construct()
		{
			actors.clear();
		}

		// �f�X�g���N�^
		void ActorSystem::Destruct()
		{
			actors.clear();
		}

		// ������
		void ActorSystem::Initialize()
		{
			for (auto actor : actors)
			{
				actor->Initialize();
			}
		}

		// �I����
		void ActorSystem::Finalize()
		{
			for (auto actor : actors)
			{
				actor->Finalize();
			}
			actors.clear();
		}

		// �X�V
		void ActorSystem::Update(Phoenix::f32 elapsedTime)
		{
			for (auto actor : actors)
			{
				actor->Update(elapsedTime);
			}
		}

		// �A�N�^�[�B���擾
		std::vector<std::shared_ptr<Actor>> ActorSystem::GetActors() const
		{
			return actors;
		}

		// �A�N�^�[���N���A
		void ActorSystem::ClearActors()
		{
			Finalize();
		}

		// �A�N�^�[��ǉ�
		void ActorSystem::AddActor(std::shared_ptr<Actor> actor)
		{
			actor->Construct();
			actors.emplace_back(actor);
		}
	}
}