#include "StateMachine.hpp"
#include "TestState.hpp"

int main()
{
    std::cout << "Powered by CGUL v" << CGUL::GetCGULVersion() << " (Compiled with: " << CGUL::GetCGULCompilerName() << ")" << std::endl;

    StateMachine stateMachine;
    stateMachine.Initialize();
    stateMachine.ChangeState(new TestState());
    while (stateMachine.IsRunning())
    {
        stateMachine.Update();
    }
    stateMachine.Exit();
}
