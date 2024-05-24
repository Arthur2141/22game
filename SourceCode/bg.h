#pragma once
#include"../GameLib/game_lib.h"
#include"player.h"
class BG
{
public:
    //------< 定数 >------------------------------------------------------------
    static const int WINDOW_W = 1920;                   // ウインドウの幅
    static const int WINDOW_H = 1080;                    // ウインドウの高さ
    static const int CLIENT_W = 1500;                   // クライアント領域の幅
    static const int CLIENT_H = 1080;                    // クライアント領域の高さ

    static const int PLAYER_SIZE_X = 110;
    static const int PLAYER_SIZE_Y = 80;

    static constexpr float WIDTH = 2920; //マップの幅
    static constexpr float HEIGHT = 1080;//マップの高さ

    static constexpr float SCROLL_MERGIN_X = 240.f;     // この数値より画面端に近づいたらスクロールする（横）
    static constexpr float SCROLL_MERGIN_Y = 160.f;     // この数値より画面端に近づいたらスクロールする（縦）
    static constexpr float ADJUST_Y = 0.25f;            // あたり判定での位置調整用（縦）
    static constexpr float ADJUST_X = 0.025f;           // あたり判定での位置調整用（横）

    static constexpr float AREA_LIMIT = 256.0f;         // 世界からこれ以上はみ出たら消える


private:
    //------< 変数 >------------------------------------------------------------
    VECTOR2 scroll;                                         // 現在表示されている左上の地点の座標
    VECTOR2* playerposition;

public:
    BG();

    // 初期化
    void init(VECTOR2* position);

    // 更新
    void update();

 
    // スクロール位置取得
    float getScrollX() { return scroll.x; }
    float getScrollY() { return scroll.y; }
    const VECTOR2& getScrollPos() { return scroll; }

  
    bool isOutOfWorld(const VECTOR2& pos);
private:
    // クリア
    void clear();

 
    // マップスクロール用
    void scrollMap();

   
    bool isUpperQuater(float);

};
