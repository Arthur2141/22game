////******************************************************************************
////
////
////      ���U���g
////
////
////******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "result.h"
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
#include "scene.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �ϐ� >----------------------------------------------------------------
Result Result::instance_;

//--------------------------------------------------------------
//  ����������
//--------------------------------------------------------------
void Result::init()
{
    Scene::init();	    // ���N���X��init���Ă�
}

//--------------------------------------------------------------
//  �I������
//--------------------------------------------------------------
void Result::deinit()
{
    // �e�N�X�`���̉��
    //texture::releaseAll();
}

//--------------------------------------------------------------
//  �X�V����
//--------------------------------------------------------------
void Result::update()
{
    using namespace input;

    switch (state_)
    {
    case 0:
        //////// �����ݒ� ////////

        // �e�N�X�`���̓ǂݍ���
        //texture::load(loadTexture);

        timer_ = 0;
        fade = 1.0f;
        GameLib::setBlendMode(Blender::BS_ALPHA);

        state_++;

        /*fallthrough*/

    case 1:
        ///// �t�F�[�h�C�� /////
        fade -= 1.0f / 60;
        if (fade <= 0.0f)
        {
            fade = 0.0f;
            state_++;
        }

        break;

    case 2:
        //////// �ʏ펞�̏��� ////////
        if (TRG(0) & PAD_START)
            state_++;

        //timer_++;
        break;

    case 3:
        ///// �t�F�[�h�A�E�g /////
        fade += 1.0f / 60;
        if (fade >= 1.0f)
            changeScene(Title::instance());  // �^�C�g���V�[���ɐ؂�ւ�
        break;
    }
    timer_++;
}

//--------------------------------------------------------------
//  �`�揈��
//--------------------------------------------------------------
void Result::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0.2f, 0.3f, 1.0f, 1));

    texture::begin(TEXNO::RESULT1);
    texture::draw(TEXNO::RESULT1, { 0, 0 }, { 1, 1 }, { 0, 0 },
        { BG::WINDOW_W, BG::WINDOW_H }, { 0, 0 });
    texture::end(TEXNO::RESULT1);

    primitive::rect({ 0, 0 }, { window::getWidth(), window::getHeight() }, { 0, 0 }, 0.0f, { 0, 0, 0, fade });
}

////******************************************************************************
