//******************************************************************************
//
//
//      �Q�[���I�[�o�[
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
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

//------< �ϐ� >----------------------------------------------------------------
Gameover Gameover::instance_;

//--------------------------------------------------------------
//  �I������
//--------------------------------------------------------------
void Gameover::deinit()
{
    // �e�N�X�`���̉��
    //texture::releaseAll();

    // ���y�̃N���A
    //music::stop(TITLE_AUDIO);
}

//--------------------------------------------------------------
//  �X�V����
//--------------------------------------------------------------
void Gameover::update()
{
    using namespace input;

    switch (state_)
    {
    case 0:
        //////// �����ݒ� ////////

        // �e�N�X�`���̓ǂݍ���
        //texture::load(loadTexture);

        //GameLib::music::play(TITLE_AUDIO, true);

        timer_ = 0;
        fade = 1.0f;
        selection = 0;
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
void Gameover::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0.2f, 0.3f, 1.0f, 1));
    texture::begin(TEXNO::GAMEOVER);
    texture::draw(TEXNO::GAMEOVER, { 0, 0 }, { 1, 1 }, { 0, 0 },
        { BG::WINDOW_W, BG::WINDOW_H }, { 0, 0 });
    texture::end(TEXNO::GAMEOVER);

    // �t�F�[�h�p
    primitive::rect({ 0, 0 }, { window::getWidth(), window::getHeight() }, { 0, 0 }, 0.0f, { 0, 0, 0, fade });
}

//******************************************************************************
