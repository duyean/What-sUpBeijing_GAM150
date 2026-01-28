#ifdef ALPHA_EDITOR
#include <vector>
#include <memory>

class EditorWindow;

class EditorApp
{
public:

    static void Init();
    static void Begin();
    static void Shutdown();

    template<typename T, typename... Args>
    static T* AddWindow(Args&&... args);

private:
    static std::vector<std::unique_ptr<EditorWindow>> sWindows;

};

#endif