#include"clear.h"
#include"../GameLib/game_lib.h"
#include"game.h"
#include"title.h"


Clear Clear::instance_;
void Clear::update()
{

    switch (state_)
    {
    case 0:
        //////// 初期設定 ////////

        timer_ = 0;                                  // タイマーを初期化
        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理
        state_++;                                    // 初期化処理の終了

        /*fallthrough*/                             // 意図的にbreak;を記述していない

    case 1:
        //////// 通常時の処理 ////////

        timer_++;                            // タイマーを足す
     //   GameLib::debug::setString("clear");

        if (GameLib::input::TRG(0) & GameLib::input::PAD_START)             // PAD_TRG1が押されたら
            changeScene(Game::instance());  // ゲームシーンに切り替え

        break;
    }
}

void Clear::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0, 0, 0, 1));
}