#include "Editor.hpp"
#include "AEEngine.h"
#ifdef ALPHA_EDITOR


LRESULT CALLBACK EditorWndProc(
    HWND hWnd,
    UINT msg,
    WPARAM wp,
    LPARAM lp
)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp))
        return true;

    return 0;

}


void ImGuiLayer::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    HWND hwnd = AESysGetWindowHandle();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL3_Init("#version 330");

}
void ImGuiLayer::Begin()
{

}
void ImGuiLayer::End()
{

}
void ImGuiLayer::Shutdown()
{

}

#endif