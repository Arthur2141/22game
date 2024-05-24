#include "../GameLib/game_lib.h"
#include "scene.h"
#include "title.h"
#include"audio.h"

int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{

    SceneManager sceneManager;
    sceneManager.execute(Title::instance());

    return 0;
}