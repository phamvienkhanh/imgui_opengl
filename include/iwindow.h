#ifndef _TEST_IMGUI_INC_IWINDOW_
#define _TEST_IMGUI_INC_IWINDOW_

class IWindow
{
public:
    virtual void Init() = 0;
    virtual void Update(double dt) = 0;
    virtual void Render() = 0;
    virtual void Render3D() = 0;

    virtual ~IWindow(){};
};

#endif