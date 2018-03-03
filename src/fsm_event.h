#pragma once



template <typename TEventType>
class FsmEvent
{
public:
    explicit FsmEvent(const TEventType& type)
        : m_type(type)
    {
    }

    const TEventType& GetType() const
    {
        return m_type;
    }

private:
    TEventType m_type;
};
