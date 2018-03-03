#pragma once
#include <functional>



template <typename TStateType, typename TEventType>
class Fsm_t;

template <typename TStateType, typename TEventType>
class FsmState_t
{
    using TFsm = Fsm_t<TStateType, TEventType>;
    friend class TFsm;

public:
    explicit FsmState_t(const TStateType& type)
        : m_type(type)
    {
    }

    virtual ~FsmState_t()
    {
    }

    const TStateType& GetType() const
    {
        return m_type;
    }

protected:
    virtual void OnEnter()
    {
    }

    virtual void OnExit()
    {
    }

    template <typename TEventType>
    bool Trigger(const TEventType& event)
    {
        return m_trigger(event);
    }

protected:
    TStateType m_type;
    std::function<bool(const TEventType&)> m_trigger;
};
