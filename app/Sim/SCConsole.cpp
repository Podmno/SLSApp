#include "SCConsole.h"

SCConsole::SCConsole(QObject *parent)
    : QObject{parent}
{

}

void SCConsole::printConsoleInfo()
{
    std::cout << "Simulation Studio CoreSimulator" << std::endl;
    std::cout << "(C) TRIStudio 2023" << std::endl;
    std::cout << "HomePage: tristudiohp.github.io" << std::endl;
    
    
}
