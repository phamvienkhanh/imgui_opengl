#include "application.h"
#include "mainwindow.h"

int main(int, char**)
{
    MainWindow* mainWind = new MainWindow();

    Application::GetInstance()->AddWindow(mainWind);

    Application::GetInstance()->Run();
    Application::GetInstance()->Cleanup();
    return 0;
}
