#include <Windows.h>
#include <gl/gl.h> 

#ifdef ALPHA_EDITOR

#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_opengl3.h"

class ImGuiLayer
{
public:
    static void Init();
    static void Begin();
    static void End();
    static void Shutdown();
};

#endif