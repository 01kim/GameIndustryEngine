#pragma once
#include "Phoenix/FrameWork/Actor/Actor.h"


class Player : public Phoenix::FrameWork::Actor
{
public:
	Player() {}
	~Player() {}

public:
	// コンストラクタ
	void DoConstruct() override;

	// デストラクタ
	void DoDestruct() override;

	// 初期化
	void DoInitialize() override;

	// 終了化
	void DoFinalize() override;

	// 更新
	void DoUpdate(Phoenix::f32 elapsedTime) override;
};

