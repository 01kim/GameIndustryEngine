#include "Player.h"
#include "Phoenix/FrameWork/Component/Transform.h"


// コンストラクタ
void Player::DoConstruct()
{

}

// デストラクタ
void Player::DoDestruct()
{

}

// 初期化
void Player::DoInitialize()
{
	auto transform = GetComponent<Phoenix::FrameWork::Transform>();
	auto translate = transform->GetTranslate();

	translate.x = 1.0f;
}

// 終了化
void Player::DoFinalize()
{

}

// 更新
void Player::DoUpdate(Phoenix::f32 elapsedTime)
{

}