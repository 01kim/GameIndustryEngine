#include "Player.h"
#include "Phoenix/FrameWork/Component/Transform.h"


// �R���X�g���N�^
void Player::DoConstruct()
{

}

// �f�X�g���N�^
void Player::DoDestruct()
{

}

// ������
void Player::DoInitialize()
{
	auto transform = GetComponent<Phoenix::FrameWork::Transform>();
	auto translate = transform->GetTranslate();

	translate.x = 1.0f;
}

// �I����
void Player::DoFinalize()
{

}

// �X�V
void Player::DoUpdate(Phoenix::f32 elapsedTime)
{

}