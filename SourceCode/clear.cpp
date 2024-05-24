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
        //////// �����ݒ� ////////

        timer_ = 0;                                  // �^�C�}�[��������
        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����
        state_++;                                    // �����������̏I��

        /*fallthrough*/                             // �Ӑ}�I��break;���L�q���Ă��Ȃ�

    case 1:
        //////// �ʏ펞�̏��� ////////

        timer_++;                            // �^�C�}�[�𑫂�
     //   GameLib::debug::setString("clear");

        if (GameLib::input::TRG(0) & GameLib::input::PAD_START)             // PAD_TRG1�������ꂽ��
            changeScene(Game::instance());  // �Q�[���V�[���ɐ؂�ւ�

        break;
    }
}

void Clear::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0, 0, 0, 1));
}