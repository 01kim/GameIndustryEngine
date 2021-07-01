#pragma once

#include <map>
#include <memory>
#include <optional>
#include "Phoenix/Math/PhoenixMath.h"


#pragma region State�p�^�[���Ŏ��������X�e�[�g�}�V��
template <class T>
class State
{
private:
	T id;

protected:
	bool canChangeState = true; // ��{�́A���ł��X�e�[�g�ڍs�ł���悤�ɂ��Ă���

public:
	State() = delete;
	explicit State(T id) : id(id) {}
	virtual ~State() = default;

public:
	// ��Ԃɓ������Ƃ��ɌĂ΂��֐�
	virtual void SetUp() = 0;

	// ���̏�ԂɈڂ�O�ɌĂ΂��֐�
	virtual void CleanUp() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime"> �o�ߎ��� </param>
	/// <returns> ���̈ڍs����X�e�[�gID </returns>
	virtual T Update(Phoenix::f32 elapsedTime) = 0;

public:
	// �X�e�[�gID�擾
	const T& GetID() { return id; }

	// �X�e�[�g�̈ڍs���ł��邩�H
	bool CanChangeState() { return canChangeState; }
};

template <class T>
class StateMachine
{
protected:
	std::map<T, std::shared_ptr<State<T>>> stateList;
	std::shared_ptr<State<T>> currentState;

public:
	StateMachine() = default;
	virtual ~StateMachine() = default;

public:
	// �X�e�[�g�}�V���̃Z�b�g�A�b�v
	virtual void SetUp() = 0;

	// �X�e�[�g�}�V���̃N���[���A�b�v
	virtual void CleanUp()
	{
		currentState.reset();
		stateList.clear();
	}

	// �X�V
	virtual T Update(Phoenix::f32 elapsedTime) = 0;

public:
	/// <summary>
	/// �X�e�[�g�ǉ�
	/// </summary>
	/// <param name="state"> �ǉ�����X�e�[�g��std::make_shared </param>
	void AddState(const std::shared_ptr<State<T>>& state)
	{
		if (state == nullptr) return;

		auto it = stateList.find(state->GetID());
		if (it != stateList.end())
		{
			return;
		}

		stateList[state->GetID()] = state;
	}

	/// <summary>
	/// �X�e�[�g�ǉ�
	/// </summary>
	/// <param name="state"> �ǉ�����X�e�[�g��std::make_shared </param>
	void RemoveState(const std::shared_ptr<State<T>>& state)
	{
		if (state == nullptr) return;

		auto it = stateList.find(state->GetID());
		if (it != stateList.end())
		{
			stateList.erase(it);
		}
	}

	/// <summary>
	/// �X�e�[�g�擾
	/// </summary>
	/// <param name="type"> �X�e�[�gID </param>
	/// <returns> �X�e�[�g </returns>
	std::shared_ptr<State<T>> GetState(T stateID)
	{
		auto it = stateList.find(stateID);
		if (it != stateList.end())
		{
			return nullptr;
		}

		return stateList[stateID];
	}

	/// <summary>
	/// ���݂̃X�e�[�gID�擾
	/// </summary>
	/// <returns> ���݂̃X�e�[�gID </returns>
	T GetCurrentStateName() const
	{
		if (currentState == nullptr)
		{
			return static_cast<T>(-1);
		}

		return currentState->GetID();
	}

	/// <summary>
	/// �w��̃X�e�[�g�ֈڍs
	/// </summary>
	/// <param name="nextStateID"> �ڍs��̃X�e�[�gID </param>
	/// <param name="forcedChange"> �����I�ɃX�e�[�g�ڍs���� </param>
	/// <returns> �X�e�[�g�ڍs���� : 0, �X�e�[�g�ڍs���s : -1 </returns>
	Phoenix::s32 GoToState(T nextStateID, bool forcedChange = false)
	{
		auto it = stateList.find(nextStateID);
		if (it == stateList.end())
		{
			return -1;
		}

		if (currentState != nullptr)
		{
			if (!currentState->CanChangeState() && !forcedChange)
			{
				return -1;
			}
			else
			{
				currentState->CleanUp();
			}
		}

		currentState = stateList[nextStateID];
		currentState->SetUp();

		return 0;
	}
};
#pragma endregion

#pragma region �e�[�u���Ŏ��������X�e�[�g�}�V��
template<class T, class... Args>
class Transition
{
private:
	T origin;      // �J�ڌ�
	T destination; // �J�ڐ�

public:
	std::function<bool(Args...)> condition; // �J�ڏ���

public:
	Transition() {}
	~Transition() {}

public:
	// ����
	static std::unique_ptr<Transition<T, Args...>> Create()
	{
		return std::make_unique<Transition<T, Args...>>();
	}

	// �J�ڏ����ǉ�
	void Add(T destination, std::function<bool(Args...)> condition)
	{
		this->destination = destination;
		this->condition = condition;
	}
	void Add(T origin, T destination, std::function<bool(Args...)> condition)
	{
		this->origin = origin;
		this->destination = destination;
		this->condition = condition;
	}

	// �J�ڌ����擾
	T GetOriginState()
	{
		return origin;
	}

	// �J�ڐ���擾
	T GetDestinationState()
	{
		return destination;
	}
};

template<class T, class... Args>
class FSM
{
private:
	// �J�ڏ���
	std::vector<std::unique_ptr<Transition<T, Args...>>> transitions;

	// AnyState�J�ڏ���
	std::vector<std::unique_ptr<Transition<T, Args...>>> transitionsOfAnyState;

	// ��ԏ�����
	std::map<T, std::function<void(Args...)>> enters;

	// ��ԍX�V
	std::map<T, std::function<void(Args...)>> updates;

	// ��ԏI����
	std::map<T, std::function<void(Args...)>> exits;

	// ���݂̃X�e�[�g
	T currentState;

public:
	FSM() {}
	~FSM() {}

public:
	// ����
	static std::shared_ptr<FSM<T, Args...>> Create()
	{
		return std::make_shared<FSM<T, Args...>>();
	}

	// �}�V���J�n�i�������j
	void Start(T startState, Args... args)
	{
		ChangeState(startState, args...);
	}

	// �X�V
	void Update(Args... args)
	{
		CheckTransition(args...);
		UpdateState(args...);
	}

	// �J�ڏ����ǉ�
	void AddTransition(T origin, T destination, std::function<bool(Args...)> condition)
	{
		Phoenix::sizeT index = transitions.size();

		transitions.emplace_back(Transition<T, Args...>::Create());
		transitions.at(index)->Add(origin, destination, condition);
	}

	// AnyState�J�ڏ����ǉ��i�ǂ̃X�e�[�g����ł��J�ڂł�������j
	void AddTransitionOfAnyState(T destination, std::function<bool(Args...)> condition)
	{
		Phoenix::sizeT index = transitionsOfAnyState.size();

		transitionsOfAnyState.emplace_back(Transition<T, Args...>::Create());
		transitionsOfAnyState.at(index)->Add(destination, condition);
	}

	// �������֐��ǉ�
	void AddEnter(T state, std::function<void(Args...)> enter)
	{
		enters.insert(std::pair<T, std::function<void(Args...)>>(state, enter));
	}

	// �X�V�֐��ǉ�
	void AddUpdate(T state, std::function<void(Args...)> update)
	{
		updates.insert(std::pair<T, std::function<void(Args...)>>(state, update));
	}

	// �I�����֐��ǉ�
	void AddExit(T state, std::function<void(Args...)> exit)
	{
		exits.insert(std::pair<T, std::function<void(Args...)>>(state, exit));
	}

	// ���݂̃X�e�[�g���擾
	T GetCurrenState()
	{
		return currentState;
	}

	/// <summary>
	/// �X�e�[�g��J��
	/// </summary>
	/// <param name="nextState"> ���Ɏ��s�������X�e�[�g </param>
	/// <param name="...args"> �ϒ����� </param>
	/// <returns> �X�e�[�g���J�ڂł������H�itrue : �����Afalse : ���s�j </returns>
	bool ChangeState(T nextState, Args... args)
	{
		// ���݂̃X�e�[�g���I��
		{
			ExitState(args...);
		}

		// �V���ȃX�e�[�g�̍X�V�֐������݂��邩�m�F
		{
			if (!CheckUpdateFunction(nextState)) return false;
		}

		// �V���ȃX�e�[�g�ɕύX
		{
			currentState = nextState;
		}

		// ���݂̃X�e�[�g�i�V���ȃX�e�[�g�j���J�n
		{
			EnterState(args...);
		}

		return true;
	}

private:
	// �J�ڂł��邩�m�F
	void CheckTransition(Args... args)
	{
		if (CheckTransitionOfAnyState(args...)) return;

		for (auto& transition : transitions)
		{
			if (currentState == transition->GetOriginState())
			{
				if (transition->condition(args...))
				{
					ChangeState(transition->GetDestinationState(), args...);
					return;
				}
			}
		}
	}

	// AnyState����J�ڂł��邩�m�F
	bool CheckTransitionOfAnyState(Args... args)
	{
		for (auto& transition : transitionsOfAnyState)
		{
			if (transition->condition(args...))
			{
				ChangeState(transition->GetDestinationState(), args...);
				return true;
			}
		}

		return false;
	}

	// ���݂̃X�e�[�g������
	void EnterState(Args... args)
	{
		auto it = enters.find(currentState);
		if (it == enters.end())
		{
			return;
		}

		enters.at(currentState)(args...);
	}

	// ���݂̃X�e�[�g�X�V
	void UpdateState(Args... args)
	{
		auto it = updates.find(currentState);
		if (it == updates.end())
		{
			return;
		}

		updates.at(currentState)(args...);
	}

	// ���݂̃X�e�[�g�I����
	void ExitState(Args... args)
	{
		auto it = exits.find(currentState);
		if (it == exits.end())
		{
			return;
		}

		exits.at(currentState)(args...);
	}

	// �X�V�֐������݂��邩�m�F
	bool CheckUpdateFunction(T state)
	{
		auto it = updates.find(state);
		if (it == updates.end())
		{
			return false;
		}

		return true;
	}
};
#pragma endregion