#pragma once



template <typename TStateType>
class FsmState_t
{
    template <typename TStateType, typename TEventType>
    friend class Fsm_t;

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

protected:
    TStateType m_type;
};
