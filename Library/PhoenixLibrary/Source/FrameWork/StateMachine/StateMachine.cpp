#include "Phoenix/FrameWork/StateMachine/StateMachine.h"


// 生成
std::unique_ptr<Transition<T, F>> Transition<T, F>::Create()
{

}

// 更新
void Update();

// 遷移条件追加
void Add(T origin, T destination, std::function<F> condition);

// 生成
std::shared_ptr<FSM> Create();

// 初期化
void Initialize();

// 終了化
void Finalize();

// 更新
void Update();

// 遷移条件追加
void AddTransition(T origin, T destination, std::function<F> condition);

// 更新関数追加
void AddUpdate(T state, std::function<void()> update);