#pragma once
#include "Phoenix/FrameWork/Actor/Actor.h"


class Player : public Phoenix::FrameWork::Actor
{
public:
	Player() {}
	~Player() {}

public:
	// �R���X�g���N�^
	void DoConstruct() override;

	// �f�X�g���N�^
	void DoDestruct() override;

	// ������
	void DoInitialize() override;

	// �I����
	void DoFinalize() override;

	// �X�V
	void DoUpdate(Phoenix::f32 elapsedTime) override;
};

