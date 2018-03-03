#pragma once



template <typename TStateType, typename TEventType>
struct FsmTransitionKey_t
{
    TStateType from;
    TEventType event;

    FsmTransitionKey_t(const TStateType& from_, const TEventType& event_)
        : from(from_)
        , event(event_)
    {
    }

    bool operator<(const FsmTransitionKey_t& rhs) const
    {
        return std::tie(from, event) < std::tie(rhs.from, rhs.event);
    }
};

template <typename TStateType, typename TEventType>
struct FsmTransition_t : public FsmTransitionKey_t<TStateType, TEventType>
{
    TStateType to;

    FsmTransition_t(const TStateType& from_, const TEventType& event_, const TStateType& to_)
        : FsmTransitionKey_t<TStateType, TEventType>(from_, event_)
        , to(to_)
    {
    }
};
