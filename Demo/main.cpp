﻿#include <iostream>
#include "../Include/fsm.h"
#include "demo.h"



int main()
{
    using TFsm = Fsm_t<eDemoState, TDemoEventType>;

    TFsm fsm;
    fsm.CreateState<DemoState>("idle", eDemoState::Idle);
    fsm.CreateState<DemoState>("walking", eDemoState::Walking);
    fsm.CreateState<DemoJumpState>();

    fsm.CreateTransition(eDemoState::Idle, WalkEvent, eDemoState::Walking);
    fsm.CreateTransition(eDemoState::Idle, JumpEvent, eDemoState::Jumping);
    fsm.CreateTransition(eDemoState::Walking, JumpEvent, eDemoState::Jumping);
    fsm.CreateTransition(eDemoState::Walking, StopEvent, eDemoState::Idle);
    fsm.CreateTransition(eDemoState::Jumping, LandEvent, eDemoState::Idle);

    if (fsm.Start(eDemoState::Idle))
    {
        using namespace std;
        bool working = true;
        while (working)
        {
            cout << endl << "W:walk, J:jump, S:stop, Q:quit" << endl;

            char c;
            cin >> c;

            switch (c)
            {
            case 'w':
            case 'W':
                fsm.Trigger(WalkEvent);
                break;

            case 'j':
            case 'J':
                fsm.Trigger(JumpEvent);
                break;

            case 's':
            case 'S':
                fsm.Trigger(StopEvent);
                break;

            case 'q':
            case 'Q':
                working = false;
                fsm.Stop();
                break;
            }
        }
    }

    return 0;
}
