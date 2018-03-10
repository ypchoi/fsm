#pragma once
#include <chrono>
#include <thread>
#include <string>
#include "../Include/fsm_state.h"



// Events
typedef const char* TDemoEventType;
static TDemoEventType WalkEvent = "walk";
static TDemoEventType JumpEvent = "jump";
static TDemoEventType StopEvent = "stop";
static TDemoEventType LandEvent = "land";

// States
enum class eDemoState
{
    Idle, Walking, Jumping
};

class DemoState : public FsmState_t<eDemoState, TDemoEventType>
{
public:
    DemoState(const char* name, eDemoState state)
        : m_name(name), m_state(state)
    {
    }

protected:
    virtual eDemoState GetType() const override { return m_state; }
    virtual void OnEnter() override { std::cout << "+ Enter : " << m_name << std::endl; }
    virtual void OnExit() override { std::cout << "- Exit : " << m_name << std::endl; }

private:
    std::string m_name;
    eDemoState m_state;
};

class DemoJumpState : public DemoState
{
public:
    DemoJumpState()
        : DemoState("jumping", eDemoState::Jumping)
    {
    }

    virtual void OnEnter() override
    {
        DemoState::OnEnter();

        std::this_thread::sleep_for(std::chrono::seconds(1));
        Trigger(LandEvent);
    }
};
