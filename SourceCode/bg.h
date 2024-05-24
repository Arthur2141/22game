#pragma once
#include"../GameLib/game_lib.h"
#include"player.h"
class BG
{
public:
    //------< �萔 >------------------------------------------------------------
    static const int WINDOW_W = 1920;                   // �E�C���h�E�̕�
    static const int WINDOW_H = 1080;                    // �E�C���h�E�̍���
    static const int CLIENT_W = 1500;                   // �N���C�A���g�̈�̕�
    static const int CLIENT_H = 1080;                    // �N���C�A���g�̈�̍���

    static const int PLAYER_SIZE_X = 110;
    static const int PLAYER_SIZE_Y = 80;

    static constexpr float WIDTH = 2920; //�}�b�v�̕�
    static constexpr float HEIGHT = 1080;//�}�b�v�̍���

    static constexpr float SCROLL_MERGIN_X = 240.f;     // ���̐��l����ʒ[�ɋ߂Â�����X�N���[������i���j
    static constexpr float SCROLL_MERGIN_Y = 160.f;     // ���̐��l����ʒ[�ɋ߂Â�����X�N���[������i�c�j
    static constexpr float ADJUST_Y = 0.25f;            // �����蔻��ł̈ʒu�����p�i�c�j
    static constexpr float ADJUST_X = 0.025f;           // �����蔻��ł̈ʒu�����p�i���j

    static constexpr float AREA_LIMIT = 256.0f;         // ���E���炱��ȏ�͂ݏo���������


private:
    //------< �ϐ� >------------------------------------------------------------
    VECTOR2 scroll;                                         // ���ݕ\������Ă��鍶��̒n�_�̍��W
    VECTOR2* playerposition;

public:
    BG();

    // ������
    void init(VECTOR2* position);

    // �X�V
    void update();

 
    // �X�N���[���ʒu�擾
    float getScrollX() { return scroll.x; }
    float getScrollY() { return scroll.y; }
    const VECTOR2& getScrollPos() { return scroll; }

  
    bool isOutOfWorld(const VECTOR2& pos);
private:
    // �N���A
    void clear();

 
    // �}�b�v�X�N���[���p
    void scrollMap();

   
    bool isUpperQuater(float);

};
