#pragma once
#include <map>
#include <memory>
#include <utility>

#include "fsm_state.h"
#include "fsm_transition.h"



template <typename TStateType, typename TEventType>
class Fsm_t
{
    using TState = FsmState_t<TStateType>;
    using TTransitionKey = FsmTransitionKey_t<TStateType, TEventType>;
    using TTransition = FsmTransition_t<TStateType, TEventType>;

public:
    Fsm_t()
        : m_current(nullptr)
    {
    }

    ~Fsm_t()
    {
    }

    template <typename T, typename... TArgs>
    bool CreateState(TArgs... args)
    {
        auto state = std::make_unique<T>(args...);
        return AddState(std::move(state));
    }

    bool AddState(std::unique_ptr<TState>&& state)
    {
        TStateType type = state->GetType();
        return m_states.insert({ type, std::move(state) }).second;
    }

    bool CreateTransition(const TStateType& from, const TEventType& event, const TStateType& to)
    {
        return AddTransition(TTransition(from, event, to));
    }

    bool AddTransition(TTransition&& transition)
    {
        auto fromIt = m_states.find(transition.from);
        if (fromIt == m_states.end())
            return false;

        auto toIt = m_states.find(transition.to);
        if (toIt == m_states.end())
            return false;

        return m_transitions.insert({ transition, toIt->second.get() }).second;
    }

    bool Start(const TStateType& initialState)
    {
        if (m_current)
            return false;

        auto it = m_states.find(initialState);
        if (it == m_states.end())
            return false;

        m_current = it->second.get();
        m_current->OnEnter();
        return true;
    }

    void Stop()
    {
        if (m_current)
        {
            m_current->OnExit();
        }
    }

    bool Trigger(const TEventType& event)
    {
        if (!m_current)
            return false;

        TTransitionKey key(m_current->GetType(), event);
        auto it = m_transitions.find(key);
        if (it == m_transitions.end())
            return false;

        m_current->OnExit();

        m_current = it->second;
        m_current->OnEnter();

        return true;
    }

private:
    std::map<TStateType, std::unique_ptr<TState>> m_states;
    std::map<TTransitionKey, TState*> m_transitions;
    TState* m_current;
};
