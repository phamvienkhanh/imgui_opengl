#ifndef _TEST_IMGUI_INC_MAINWINDOW_
#define _TEST_IMGUI_INC_MAINWINDOW_

#include "iwindow.h"
#include <imgui.h>

class MainWindow: public IWindow
{
public:
    virtual void Init() override;
    virtual void Update(double dt) override;
    virtual void Render() override;

    virtual void Render3D() override;

    MainWindow();
    ~MainWindow();

private:
    ImVec4 m_trangleColor;
};

#endif