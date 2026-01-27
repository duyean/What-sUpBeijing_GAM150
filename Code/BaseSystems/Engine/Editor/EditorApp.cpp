#ifdef ALPHA_EDITOR
#include "EditorApp.h"
#include "EditorWindow.h"

std::vector<std::unique_ptr<EditorWindow>> EditorApp::s_Windows;

void EditorApp::Init()
{
    AddWindow<SceneViewWindow>();
    // AddWindow<InspectorWindow>();
}

void EditorApp::Draw()
{
    for (auto& window : s_Windows)
    {
        if (window->IsOpen())
            window->OnDraw();
    }
}

void EditorApp::Shutdown()
{
    s_Windows.clear();
}

template<typename T, typename... Args>
T* EditorApp::AddWindow(Args&&... args)
{
    s_Windows.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    return static_cast<T*>(s_Windows.back().get());
}
#endif
