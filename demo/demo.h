#pragma once
#include <string>
#include "../src/fsm_state.h"



enum class eDemoState
{
    Idle, Walking, Jumping
};

class DemoState : public FsmState_t<eDemoState>
{
public:
    DemoState(const char* name, eDemoState state)
        : FsmState_t<eDemoState>(state)
        , m_name(name)
    {
    }

protected:
    virtual void OnEnter() override { std::cout << "+ Enter : " << m_name << std::endl; }
    virtual void OnExit() override { std::cout << "- Exit : " << m_name << std::endl; }

private:
    std::string m_name;
};

static const char* WalkEvent = "walk";
static const char* JumpEvent = "jump";
static const char* StopEvent = "stop";
static const char* LandEvent = "land";
