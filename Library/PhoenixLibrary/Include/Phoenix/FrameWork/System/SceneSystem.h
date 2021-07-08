#pragma once

#include <map>
#include "Phoenix/Math/PhoenixMath.h"
#include "Phoenix/FrameWork/System/System.h"
#include "Phoenix/FrameWork/System/ActorSystem.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class IScene
		{
		protected:
			// �A�N�^�[�Ǘ��i�v���C���[�A�G�l�~�[�A�X�e�[�W etc...�j
			std::shared_ptr<ActorSystem> actorSystem;

		public:
			IScene() {}
			virtual ~IScene() {}

		public:
			// �R���X�g���N�^
			void Construct();
			virtual void DoConstruct() = 0;

			// �f�X�g���N�^
			void Destruct();
			virtual void DoDestruct() = 0;

			// ������
			void Initialize();
			virtual void DoInitialize() = 0;

			// �I����
			void Finalize();
			virtual void DoFinalize() = 0;

			// �X�V
			void Update(Phoenix::f32 elapsedTime);
			virtual void DoUpdate(Phoenix::f32 elapsedTime) = 0;

			// �`��
			void Draw(Phoenix::f32 elapsedTime);

			// �A�N�^�[�Ǘ��N���X��ݒ�
			void SetActorSystem(std::shared_ptr<ActorSystem> actorSystem);
		};

		class SceneSystem : public ISystem
		{
		private:
			std::vector<std::shared_ptr<IScene>> scenes;
			std::shared_ptr<IScene> currentScene;
			std::shared_ptr<IScene> nextScene;

		private:
			// �A�N�^�[�Ǘ��i�v���C���[�A�G�l�~�[�A�X�e�[�W etc...�j
			std::shared_ptr<ActorSystem> actorSystem;

		public:
			SceneSystem() {}
			~SceneSystem() override {}

		public:
			// ����
			static std::shared_ptr<SceneSystem> Create();

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
			void Draw(Phoenix::f32 elapsedTime);

			// �A�N�^�[�Ǘ��N���X��ݒ�
			void SetActorSystem(std::shared_ptr<ActorSystem> actorSystem);

		private:
			// �V�[����ǉ�
			void AddScene(std::shared_ptr<IScene> scene);

		public:
			// �V�[��������
			template<class T>
			std::shared_ptr<T> GetScene()
			{
				for (auto scene : scenes)
				{
					std::shared_ptr<T> buff = std::dynamic_pointer_cast<std::shared_ptr<T>>(scene);
					if (buff != nullptr)
					{
						return buff;
					}
				}
				return nullptr;
			}

			// �V�[����ǉ�
			template<class T>
			std::shared_ptr<T> AddScene()
			{
				std::shared_ptr<T> scene = std::make_shared<T>();
				AddScene(scene);

				return scene;
			}

			// �V�[�����폜
			template<class T>
			void RemoveScene()
			{
				Phoenix::s32 cnt = 0;
				for (auto scene : scenes)
				{
					std::shared_ptr<T> buff = std::dynamic_pointer_cast<std::shared_ptr<T>>(scene);
					if (buff != nullptr)
					{
						break;
					}
					++cnt;
				}

				scenes.erase(scenes.begin() + cnt);
			}

			//	�V�[���̐؂�ւ�
			template<class T>
			void ChangeScene()
			{
				std::shared_ptr<T> scene = GetScene<T>();
				if (scene != nullptr)
				{
					nextScene = scene;
				}
			}
		};
	}
}