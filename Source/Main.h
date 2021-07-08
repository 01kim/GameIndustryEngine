#pragma once
#include <stdio.h>
#include <memory>
#include "Phoenix/Types.h"
#include "Phoenix/FND/Util.h"
#include "Phoenix/FrameWork/Main.h"
#include "Phoenix/Math/PhoenixMath.h"
#include "Phoenix/Loader/Loader.h"
#include "Phoenix/OS/Path.h"
#include "Phoenix/OS/Resource.h"
#include "Phoenix/Graphics/Shader.h"
#include "Phoenix/Graphics/Model.h"
#include "Phoenix/Graphics/Camera.h"
#include "Phoenix/Graphics/Shader.h"
#include "Phoenix/FrameWork/Renderer/Renderer.h"
#include "Phoenix/FrameWork/Object/Object.h"
#include "Phoenix/FrameWork/Shader/Shader.h"
#include "Phoenix/FrameWork/System/ActorSystem.h"
#include "Phoenix/FrameWork/System/SceneSystem.h"
#include "../Source/Loader/Loader.h"
#include "imgui.h"


//****************************************************************************
// ���C��
//****************************************************************************
class Main : public Phoenix::FrameWork::Main
{
private:
	using Super = Phoenix::FrameWork::Main;

private:
	// �A�N�^�[�Ǘ��i�v���C���[�A�G�l�~�[�A�X�e�[�W etc...�j
	std::shared_ptr<Phoenix::FrameWork::ActorSystem> actorSystem;

	// �V�[���Ǘ��i�^�C�g���A�Q�[���A�Q�[���N���A�A�Q�[���I�[�o�[ etc...�j
	std::shared_ptr<Phoenix::FrameWork::SceneSystem> sceneSystem;

public:
	Main() {}
	~Main() {}

public:
	// ������
	bool DoInitialize() override;
};