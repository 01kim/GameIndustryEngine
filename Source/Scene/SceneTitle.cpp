#include "SceneTitle.h"
#include "../Player/Player.h"


// コンストラクタ
void SceneTitle::DoConstruct()
{
	
}

// デストラクタ
void SceneTitle::DoDestruct()
{

}

// 初期化
void SceneTitle::DoInitialize()
{
	// アクター追加（プレイヤー、エネミー、ステージ etc...）
	{
		actorSystem->AddActor<Player>();
	}
}

// 終了化
void SceneTitle::DoFinalize()
{

}

// 更新
void SceneTitle::DoUpdate(Phoenix::f32 elapsedTime)
{

}