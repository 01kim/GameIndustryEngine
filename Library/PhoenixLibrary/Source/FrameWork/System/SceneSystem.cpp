#include "pch.h"
#include "Phoenix/FrameWork/System/SceneSystem.h"


namespace Phoenix
{
	namespace FrameWork
	{
		// �R���X�g���N�^
		void IScene::Construct()
		{
			DoConstruct();
		}

		// �f�X�g���N�^
		void IScene::Destruct()
		{
			DoDestruct();
		}

		// ������
		void IScene::Initialize()
		{
			// �A�N�^�[���Ǘ�����z���������
			actorSystem->ClearActors();

			DoInitialize();
		}

		// �I����
		void IScene::Finalize()
		{
			DoFinalize();
		}

		// �X�V
		void IScene::Update(Phoenix::f32 elapsedTime)
		{
			DoUpdate(elapsedTime);
		}

		// �`��
		void IScene::Draw(Phoenix::f32 elapsedTime)
		{

		}

		// �A�N�^�[�Ǘ��N���X��ݒ�
		void IScene::SetActorSystem(std::shared_ptr<ActorSystem> actorSystem)
		{
			this->actorSystem = actorSystem;
		}

		// ����
		std::shared_ptr<SceneSystem> SceneSystem::Create()
		{
			return std::make_shared<SceneSystem>();
		}

		// �R���X�g���N�^
		void SceneSystem::Construct()
		{

		}

		// �f�X�g���N�^
		void SceneSystem::Destruct()
		{
			nextScene.reset();
			currentScene.reset();
			scenes.clear();
		}

		// ������
		void SceneSystem::Initialize()
		{

		}

		// �I����
		void SceneSystem::Finalize()
		{
			nextScene.reset();
			currentScene.reset();
			scenes.clear();
		}

		// �X�V
		void SceneSystem::Update(Phoenix::f32 elapsedTime)
		{
			if (!currentScene) return;

			if (nextScene)
			{
				currentScene = nextScene;
				currentScene->Initialize();
				nextScene.reset();
			}

			currentScene->Update(elapsedTime);
		}

		// �`��
		void SceneSystem::Draw(Phoenix::f32 elapsedTime)
		{
			if (!currentScene) return;
			currentScene->Draw(elapsedTime);
		}

		// �A�N�^�[�Ǘ��N���X��ݒ�
		void SceneSystem::SetActorSystem(std::shared_ptr<ActorSystem> actorSystem)
		{
			this->actorSystem = actorSystem;
		}

		// �V�[����ǉ�
		void SceneSystem::AddScene(std::shared_ptr<IScene> scene)
		{
			scene->Construct();
			scene->SetActorSystem(actorSystem);
			scenes.emplace_back(scene);
		}
	}
}