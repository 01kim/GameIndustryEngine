#include "SceneTitle.h"
#include "../Player/Player.h"


// �R���X�g���N�^
void SceneTitle::DoConstruct()
{
	
}

// �f�X�g���N�^
void SceneTitle::DoDestruct()
{

}

// ������
void SceneTitle::DoInitialize()
{
	// �A�N�^�[�ǉ��i�v���C���[�A�G�l�~�[�A�X�e�[�W etc...�j
	{
		actorSystem->AddActor<Player>();
	}
}

// �I����
void SceneTitle::DoFinalize()
{

}

// �X�V
void SceneTitle::DoUpdate(Phoenix::f32 elapsedTime)
{

}