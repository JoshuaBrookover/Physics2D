#include "StateMachine.hpp"
#include "StateBoxes.hpp"

#include <iostream>

int main()
{
    std::cout << "Powered by CGUL v" << CGUL::GetCGULVersion() << " (Compiled with: " << CGUL::GetCGULCompilerName() << ")" << std::endl;

    StateMachine stateMachine;
    stateMachine.Initialize();
    stateMachine.ChangeState(new StateBoxes());
    while (stateMachine.IsRunning())
    {
        stateMachine.Update();
    }
    stateMachine.Exit();
}
