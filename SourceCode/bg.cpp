#include"bg.h"
#include"player.h"
#include"sprite_data.h"
//----------------------------------------------------------------------
//  コンストラクタ
//----------------------------------------------------------------------
BG::BG()
    :scroll(VECTOR2(0, 0))
{

}

void BG::init(VECTOR2* player_position)
{
    playerposition = player_position;

    // BG用データのクリア
    clear();
}

void BG::clear()
{
    scroll = {0,0};    // スクロール座標（画面左上の位置のワールド座標）
}

void BG::update()
{
    scrollMap();
}

void BG::scrollMap()
{
    // スクロール処理
    // 右方向のスクロール処理
   
    if (scroll.x < playerposition->x +  - CLIENT_W + SCROLL_MERGIN_X)
        scroll.x = playerposition->x +  - CLIENT_W + SCROLL_MERGIN_X;

    // 左方向のスクロール処理
    if (scroll.x > playerposition->x  - SCROLL_MERGIN_X)
        scroll.x = playerposition->x  - SCROLL_MERGIN_X;


    // エリア制限（右）
    if (scroll.x > 960) scroll.x = 960;

    // エリア制限（左）
    if (scroll.x <-960) scroll.x = -960;

    // エリア制限（下）
    if (scroll.y > BG::HEIGHT - CLIENT_H) scroll.y = BG::HEIGHT - CLIENT_H;

    // エリア制限（上）
    if (scroll.y < 0) scroll.y = 0;
}



bool BG::isOutOfWorld(const VECTOR2& pos)
{
    if (pos.x < -AREA_LIMIT) return true;
    if (pos.x > WIDTH + AREA_LIMIT) return true;
    if (pos.y < -AREA_LIMIT) return true;
    if (pos.y > HEIGHT + AREA_LIMIT) return true;

    return false;
}

bool BG::isUpperQuater(float y)
{
    return static_cast<int>(y) % PLAYER_SIZE_Y < PLAYER_SIZE_Y / 4;
}
