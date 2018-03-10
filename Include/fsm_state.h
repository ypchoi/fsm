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
    explicit FsmState_t() {}
    virtual ~FsmState_t() {}

    virtual TStateType GetType() const = 0;

protected:
    virtual void OnEnter() {}
    virtual void OnExit() {}

    template <typename TEventType>
    bool Trigger(const TEventType& event)
    {
        return m_trigger(event);
    }

protected:
    std::function<bool(const TEventType&)> m_trigger;
};
