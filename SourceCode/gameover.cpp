//******************************************************************************
//
//
//      ゲームオーバー
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "gameover.h"
#include "sprite_data.h"
#include "game.h"
#include "math.h"
#include "../GameLib/depth_stencil.h"
#include "audio.h"
#include "Input/Input.h"
#include "sprite_data.h"
#include "title.h"
#include "tutorial.h"
#include "bg.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< 変数 >----------------------------------------------------------------
Gameover Gameover::instance_;

//--------------------------------------------------------------
//  終了処理
//--------------------------------------------------------------
void Gameover::deinit()
{
    // テクスチャの解放
    //texture::releaseAll();

    // 音楽のクリア
    //music::stop(TITLE_AUDIO);
}

//--------------------------------------------------------------
//  更新処理
//--------------------------------------------------------------
void Gameover::update()
{
    using namespace input;

    switch (state_)
    {
    case 0:
        //////// 初期設定 ////////

        // テクスチャの読み込み
        //texture::load(loadTexture);

        //GameLib::music::play(TITLE_AUDIO, true);

        timer_ = 0;
        fade = 1.0f;
        selection = 0;
        GameLib::setBlendMode(Blender::BS_ALPHA);
        state_++;

        /*fallthrough*/

    case 1:
        ///// フェードイン /////
        fade -= 1.0f / 60;
        if (fade <= 0.0f)
        {
            fade = 0.0f;
            state_++;
        }

        break;

    case 2:
        //////// 通常時の処理 ////////
        if (TRG(0) & PAD_START)
            state_++;

        break;

    case 3:
        ///// フェードアウト /////
        fade += 1.0f / 60;
        if (fade >= 1.0f)
            changeScene(Title::instance());  // タイトルシーンに切り替え
        break;
    }
    timer_++;
}

//--------------------------------------------------------------
//  描画処理
//--------------------------------------------------------------
void Gameover::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0.2f, 0.3f, 1.0f, 1));
    texture::begin(TEXNO::GAMEOVER);
    texture::draw(TEXNO::GAMEOVER, { 0, 0 }, { 1, 1 }, { 0, 0 },
        { BG::WINDOW_W, BG::WINDOW_H }, { 0, 0 });
    texture::end(TEXNO::GAMEOVER);

    // フェード用
    primitive::rect({ 0, 0 }, { window::getWidth(), window::getHeight() }, { 0, 0 }, 0.0f, { 0, 0, 0, fade });
}

//******************************************************************************
