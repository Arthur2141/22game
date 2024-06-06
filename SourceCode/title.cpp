#include"title.h"
#include<sstream>
#include"../GameLib/game_lib.h"
#include"sprite_data.h"
#include"game.h"
#include"math.h"
#include"../GameLib/depth_stencil.h"
#include"audio.h"
#include "Input/Input.h"
#include "bg.h" 
#include "tutorial.h"
using namespace GameLib;
Title Title::instance_;
void Title::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ

    selection = 0;
}

void Title::deinit()
{
    // テクスチャの解放
    //texture::releaseAll();
}

bool isInit = false;

void Title::update()
{
    using namespace input;
    switch (state_)
    {
    case 0:
        // 初期設定
        if (isInit == false)
        {
            isInit = true;
            texture::load(loadTexture);
        }
        timer_ = 0;
        fade = 1.0f;
        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
        state_++;
        //GameLib::texture::load(loadTexture);
        /*fallthrough*/
    case 1:
        // フェードイン処理
        fade -= 1.0f / 60;
        if (fade <= 0.0f)
        {
            fade = 0.0f;
            state_++;
        }
        break;
    case 2:
        // 通常時の処理

        // キーボード入力処理
        if (input::TRG(0) & input::PAD_UP) {
            selection = (selection - 1 + 2) % 2; // 上キーで選択肢を変更
        }
        if (input::TRG(0) & input::PAD_DOWN) {
            selection = (selection + 1) % 2; // 下キーで選択肢を変更
        }
        if (input::TRG(0) & input::PAD_START) {
            state_++; // エンターキーでフェードアウト開始
        }

        break;
    case 3:
        // フェードアウト処理
        fade += 1.0f / 60;
        if (fade >= 1.0f)
        {
            switch (selection)
            {
            case 0: // ゲームシーンに切り替え
                changeScene(Game::instance());
                break;
            case 1: // チュートリアルシーンに切り替え
                changeScene(Tutorial::instance());
                break;
            }
        }
        break;
    }
    timer_++;
}
//
//void Title::draw()
//{
//    // 画面クリア
//    GameLib::clear(VECTOR4(0, 0,0, 1));
//
//   // DepthStencil::instance().set(DepthStencil::MODE::NONE);
//   //DepthStencil::instance().set(DepthStencil::MODE::MASK);
//   // GameLib::primitive::rect({ 1920/2, 1080/2 }, { rect_size_x,rect_size_y }, { 960, 540 }, 0, { 0, 0, 0, 1 });
//   // GameLib::primitive::rect({ 1920, 1080 }, { rect_size_x,rect_size_y }, { 1920, 1080 }, 0, { 0, 0, 0, 1 });
//   // GameLib::primitive::circle(1920 / 2, 1080 / 2, rect_size_x, 1, 1, timer_*0.005f, 1, 1, 1, 1, 10);
//   // DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);
//   // DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);
//
//    texture::begin(TEXNO::TITLE);
//    texture::draw(TEXNO::TITLE, { 0, 0 }, { 1, 1 }, { 0, 0 },
//        { BG::WINDOW_W, BG::WINDOW_H }, { 0, 0 } );
//    texture::end(TEXNO::TITLE);
//
//    primitive::circle( 1920/2,1080/2,6,
//        1.0, 1.0,   0.0,   0.0, 0.0, 1.0);
//
//    primitive::rect({ 0, 0 }, { window::getWidth(), window::getHeight() }, { 0, 0 }, 0.0f, { 0, 0, 0, fade });
//}

void Title::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0, 0, 0, 1));

    texture::begin(TEXNO::TITLE);
    texture::draw(TEXNO::TITLE, { 0, 0 }, { 1, 1 }, { 0, 0 },
        { BG::WINDOW_W, BG::WINDOW_H }, { 0, 0 });
    texture::end(TEXNO::TITLE);

  
    // 選択肢のハイライト描画
    const float OPTION_Y_OFFSET = 200.0f; // 選択肢のY座標の開始位置
    const float OPTION_SPACING = 50.0f;   // 選択肢間の間隔

    for (int i = 0; i < 2; ++i) {
        if (i == selection) {
            // 選択中のオプションを強調表示
            primitive::rect({ 90.0f, OPTION_Y_OFFSET + i * OPTION_SPACING - 10.0f }, { 320.0f, 60.0f }, { 0.0f, 0.0f }, 0.0f, { 1.0f, 1.0f, 0.0f, 1.0f });
        }
    }

    // フェードエフェクトの描画
    primitive::rect({ 0, 0 }, { window::getWidth(), window::getHeight() }, { 0, 0 }, 0.0f, { 0, 0, 0, fade });
}