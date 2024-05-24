#include"bg.h"
#include"player.h"
#include"sprite_data.h"
//----------------------------------------------------------------------
//  �R���X�g���N�^
//----------------------------------------------------------------------
BG::BG()
    :scroll(VECTOR2(0, 0))
{

}

void BG::init(VECTOR2* player_position)
{
    playerposition = player_position;

    // BG�p�f�[�^�̃N���A
    clear();
}

void BG::clear()
{
    scroll = {0,0};    // �X�N���[�����W�i��ʍ���̈ʒu�̃��[���h���W�j
}

void BG::update()
{
    scrollMap();
}

void BG::scrollMap()
{
    // �X�N���[������
    // �E�����̃X�N���[������
   
    if (scroll.x < playerposition->x +  - CLIENT_W + SCROLL_MERGIN_X)
        scroll.x = playerposition->x +  - CLIENT_W + SCROLL_MERGIN_X;

    // �������̃X�N���[������
    if (scroll.x > playerposition->x  - SCROLL_MERGIN_X)
        scroll.x = playerposition->x  - SCROLL_MERGIN_X;


    // �G���A�����i�E�j
    if (scroll.x > 960) scroll.x = 960;

    // �G���A�����i���j
    if (scroll.x <-960) scroll.x = -960;

    // �G���A�����i���j
    if (scroll.y > BG::HEIGHT - CLIENT_H) scroll.y = BG::HEIGHT - CLIENT_H;

    // �G���A�����i��j
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
