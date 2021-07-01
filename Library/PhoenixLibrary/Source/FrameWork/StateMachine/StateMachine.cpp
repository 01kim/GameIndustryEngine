#include "Phoenix/FrameWork/StateMachine/StateMachine.h"


// ����
std::unique_ptr<Transition<T, F>> Transition<T, F>::Create()
{

}

// �X�V
void Update();

// �J�ڏ����ǉ�
void Add(T origin, T destination, std::function<F> condition);

// ����
std::shared_ptr<FSM> Create();

// ������
void Initialize();

// �I����
void Finalize();

// �X�V
void Update();

// �J�ڏ����ǉ�
void AddTransition(T origin, T destination, std::function<F> condition);

// �X�V�֐��ǉ�
void AddUpdate(T state, std::function<void()> update);