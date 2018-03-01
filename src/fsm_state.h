#pragma once


template <typename TType>
class FsmState
{
public:
    explicit FsmState(const TType& type)
        : m_type(type)
    {
    }

    TType GetType() const
    {
        return m_type;
    }

private:
    TType m_type;
};
