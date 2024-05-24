#include"../GameLib/game_lib.h"
#include"../GameLib/depth_stencil.h"
#include"scene.h"
#include"common.h"
#include"audio.h"
Scene* Scene::execute()
{

    // 初期化処理
    init();

    // ゲームループ
    while (GameLib::gameLoop(false))    // falseをtrueにするとタイトルバーにフレームレート表示
    {
        // 入力処理
        GameLib::input::update();

        // 更新処理
        update();

        // ステンシルモード：通常
        DepthStencil::instance().set(DepthStencil::MODE::NONE);

        // 描画処理
        draw();

        // ステンシルモード：通常
        DepthStencil::instance().set(DepthStencil::MODE::NONE);

        // デバッグ文字列の描画
        GameLib::debug::display(1, 1, 1, 1, 1);
        //debug::setString("GP2_12 SAMPLE");

        // 画面フリップ
        GameLib::present(1, 0);

        // 終了チェック
        if (nextScene_) break;
    }

    // 終了処理
    deinit();

    return nextScene_;	// 次のシーンを返す
}

void SceneManager::execute(Scene* scene)
{

    using namespace GameLib;

    bool isFullScreen = false;	// フルスクリーンにするならtrueに変える
    //（Releaseモードのみ）

// ゲームライブラリの初期化処理
    int w = static_cast<int>(SCREEN_W);
    int h = static_cast<int>(SCREEN_H);
    GameLib::init(L"game2-2", w, h, isFullScreen);
    audio_init();
    GameLib::music::update();

#ifndef _DEBUG
    ShowCursor(!isFullScreen);	// フルスクリーン時はカーソルを消す
#endif

    // メインループ
    while (scene)
    {
        scene = scene->execute();
    }

    // ゲームライブラリの終了処理
    GameLib::uninit();
}
