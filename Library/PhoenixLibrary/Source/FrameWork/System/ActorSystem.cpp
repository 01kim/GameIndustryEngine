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

		}

		// �f�X�g���N�^
		void ActorSystem::Destruct()
		{

		}

		// ������
		void ActorSystem::Initialize()
		{

		}

		// �I����
		void ActorSystem::Finalize()
		{

		}

		// �X�V
		void ActorSystem::Update(Phoenix::f32 elapsedTime)
		{

		}

		// �A�N�^�[�B���擾
		std::vector<std::shared_ptr<Actor>> ActorSystem::GetActors() const
		{
			return actors;
		}
	}
}