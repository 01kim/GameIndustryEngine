#pragma once

#include <map>
#include <memory>
#include <optional>
#include "Phoenix/Math/PhoenixMath.h"


#pragma region Stateパターンで実装したステートマシン
template <class T>
class State
{
private:
	T id;

protected:
	bool canChangeState = true; // 基本は、いつでもステート移行できるようにしておく

public:
	State() = delete;
	explicit State(T id) : id(id) {}
	virtual ~State() = default;

public:
	// 状態に入ったときに呼ばれる関数
	virtual void SetUp() = 0;

	// 次の状態に移る前に呼ばれる関数
	virtual void CleanUp() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime"> 経過時間 </param>
	/// <returns> 次の移行するステートID </returns>
	virtual T Update(Phoenix::f32 elapsedTime) = 0;

public:
	// ステートID取得
	const T& GetID() { return id; }

	// ステートの移行ができるか？
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
	// ステートマシンのセットアップ
	virtual void SetUp() = 0;

	// ステートマシンのクリーンアップ
	virtual void CleanUp()
	{
		currentState.reset();
		stateList.clear();
	}

	// 更新
	virtual T Update(Phoenix::f32 elapsedTime) = 0;

public:
	/// <summary>
	/// ステート追加
	/// </summary>
	/// <param name="state"> 追加するステートのstd::make_shared </param>
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
	/// ステート追加
	/// </summary>
	/// <param name="state"> 追加するステートのstd::make_shared </param>
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
	/// ステート取得
	/// </summary>
	/// <param name="type"> ステートID </param>
	/// <returns> ステート </returns>
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
	/// 現在のステートID取得
	/// </summary>
	/// <returns> 現在のステートID </returns>
	T GetCurrentStateName() const
	{
		if (currentState == nullptr)
		{
			return static_cast<T>(-1);
		}

		return currentState->GetID();
	}

	/// <summary>
	/// 指定のステートへ移行
	/// </summary>
	/// <param name="nextStateID"> 移行先のステートID </param>
	/// <param name="forcedChange"> 強制的にステート移行する </param>
	/// <returns> ステート移行成功 : 0, ステート移行失敗 : -1 </returns>
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

#pragma region テーブルで実装したステートマシン
template<class T, class... Args>
class Transition
{
private:
	T origin;      // 遷移元
	T destination; // 遷移先

public:
	std::function<bool(Args...)> condition; // 遷移条件

public:
	Transition() {}
	~Transition() {}

public:
	// 生成
	static std::unique_ptr<Transition<T, Args...>> Create()
	{
		return std::make_unique<Transition<T, Args...>>();
	}

	// 遷移条件追加
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

	// 遷移元を取得
	T GetOriginState()
	{
		return origin;
	}

	// 遷移先を取得
	T GetDestinationState()
	{
		return destination;
	}
};

template<class T, class... Args>
class FSM
{
private:
	// 遷移条件
	std::vector<std::unique_ptr<Transition<T, Args...>>> transitions;

	// AnyState遷移条件
	std::vector<std::unique_ptr<Transition<T, Args...>>> transitionsOfAnyState;

	// 状態初期化
	std::map<T, std::function<void(Args...)>> enters;

	// 状態更新
	std::map<T, std::function<void(Args...)>> updates;

	// 状態終了化
	std::map<T, std::function<void(Args...)>> exits;

	// 現在のステート
	T currentState;

public:
	FSM() {}
	~FSM() {}

public:
	// 生成
	static std::shared_ptr<FSM<T, Args...>> Create()
	{
		return std::make_shared<FSM<T, Args...>>();
	}

	// マシン開始（初期化）
	void Start(T startState, Args... args)
	{
		ChangeState(startState, args...);
	}

	// 更新
	void Update(Args... args)
	{
		CheckTransition(args...);
		UpdateState(args...);
	}

	// 遷移条件追加
	void AddTransition(T origin, T destination, std::function<bool(Args...)> condition)
	{
		Phoenix::sizeT index = transitions.size();

		transitions.emplace_back(Transition<T, Args...>::Create());
		transitions.at(index)->Add(origin, destination, condition);
	}

	// AnyState遷移条件追加（どのステートからでも遷移できる条件）
	void AddTransitionOfAnyState(T destination, std::function<bool(Args...)> condition)
	{
		Phoenix::sizeT index = transitionsOfAnyState.size();

		transitionsOfAnyState.emplace_back(Transition<T, Args...>::Create());
		transitionsOfAnyState.at(index)->Add(destination, condition);
	}

	// 初期化関数追加
	void AddEnter(T state, std::function<void(Args...)> enter)
	{
		enters.insert(std::pair<T, std::function<void(Args...)>>(state, enter));
	}

	// 更新関数追加
	void AddUpdate(T state, std::function<void(Args...)> update)
	{
		updates.insert(std::pair<T, std::function<void(Args...)>>(state, update));
	}

	// 終了化関数追加
	void AddExit(T state, std::function<void(Args...)> exit)
	{
		exits.insert(std::pair<T, std::function<void(Args...)>>(state, exit));
	}

	// 現在のステートを取得
	T GetCurrenState()
	{
		return currentState;
	}

	/// <summary>
	/// ステートを遷移
	/// </summary>
	/// <param name="nextState"> 次に実行したいステート </param>
	/// <param name="...args"> 可変長引数 </param>
	/// <returns> ステートが遷移できたか？（true : 成功、false : 失敗） </returns>
	bool ChangeState(T nextState, Args... args)
	{
		// 現在のステートを終了
		{
			ExitState(args...);
		}

		// 新たなステートの更新関数が存在するか確認
		{
			if (!CheckUpdateFunction(nextState)) return false;
		}

		// 新たなステートに変更
		{
			currentState = nextState;
		}

		// 現在のステート（新たなステート）を開始
		{
			EnterState(args...);
		}

		return true;
	}

private:
	// 遷移できるか確認
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

	// AnyStateから遷移できるか確認
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

	// 現在のステート初期化
	void EnterState(Args... args)
	{
		auto it = enters.find(currentState);
		if (it == enters.end())
		{
			return;
		}

		enters.at(currentState)(args...);
	}

	// 現在のステート更新
	void UpdateState(Args... args)
	{
		auto it = updates.find(currentState);
		if (it == updates.end())
		{
			return;
		}

		updates.at(currentState)(args...);
	}

	// 現在のステート終了化
	void ExitState(Args... args)
	{
		auto it = exits.find(currentState);
		if (it == exits.end())
		{
			return;
		}

		exits.at(currentState)(args...);
	}

	// 更新関数が存在するか確認
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