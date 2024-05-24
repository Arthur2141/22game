#include"retry.h"
#include"../GameLib/game_lib.h"
#include"game.h"
#include"title.h"


Retry Retry::instance_;
void Retry::update()
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

      //  GameLib::debug::setString("retry");
        changeScene(Game::instance());  // �Q�[���V�[���ɐ؂�ւ�
        
        break;
    }
}

void Retry::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0, 0, 0, 1));
}