#pragma once

#include <memory>
#include "Phoenix/Math/PhoenixMath.h"


namespace Phoenix
{
	namespace FrameWork
	{
		class Actor;
		class Component
		{
		public:
			std::weak_ptr<Actor> owner;

		public:
			Component() {}
			virtual ~Component() {}

		public:
			// �������Ɉ�x�����Ă΂��
			virtual void Awake() {}

			// ������
			virtual void Start() {}

			// �X�V
			virtual void Update(Phoenix::f32 elapsedTime) {}

		public:
			// �I�[�i�[�ݒ�
			void SetOwner(std::shared_ptr<Actor> actor) { owner = actor; }

			// �I�[�i�[�擾
			std::shared_ptr<Actor> GetOwner() { return owner.lock(); }
		};
	}
}