#include"title.h"
#include<sstream>
#include"../GameLib/game_lib.h"
#include"sprite_data.h"
#include"game.h"
#include"math.h"
#include"../GameLib/depth_stencil.h"
#include"audio.h"
#include "Input/Input.h"
Title Title::instance_;
void Title::update()
{

    switch (state_)
    {
    case 0:
        //////// 初期設定 ////////


     
        
        timer_ = 0;      
        // タイマーを初期化
        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理
        state_++;                                    // 初期化処理の終了
        GameLib::texture::load(loadTexture);
        /*fallthrough*/                             // 意図的にbreak;を記述していない

    case 1:
        //////// 通常時の処理 ////////
     // GameLib::input::
      
      //Mouse& mouse = Input::Instance().GetMouse();
      //  if (mouse.GetButtonDown() & mouse.BTN_LEFT)
      //  {
      //      changeScene(Game::instance());  // ゲームシーンに切り替え
      //  }
      if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
      {
        changeScene(Game::instance());
      }

        timer_++;                            // タイマーを足す
        break;
    }
}

void Title::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0, 0,0, 1));

    DepthStencil::instance().set(DepthStencil::MODE::NONE);
    DepthStencil::instance().set(DepthStencil::MODE::MASK);
   // GameLib::primitive::rect({ 1920/2, 1080/2 }, { rect_size_x,rect_size_y }, { 960, 540 }, 0, { 0, 0, 0, 1 });
   // GameLib::primitive::rect({ 1920, 1080 }, { rect_size_x,rect_size_y }, { 1920, 1080 }, 0, { 0, 0, 0, 1 });
    GameLib::primitive::circle(1920 / 2, 1080 / 2, rect_size_x, 1, 1, timer_*0.005f, 1, 1, 1, 1, 10);
    DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);
    DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);


}