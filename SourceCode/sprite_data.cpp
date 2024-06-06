
#include"sprite_data.h"

using namespace GameLib;

void texture_draw(int texNo, const VECTOR2& pos, const VECTOR2& scale, const VECTOR2& texPos,
	const VECTOR2& texSize, const VECTOR2& center, float angle, const VECTOR4& color, bool world)
{
	texture::begin(texNo);
	texture::draw(texNo, pos, scale, texPos, texSize, center, angle, color, world);
	texture::end(texNo);
}

GameLib::LoadTexture loadTexture[] =
{
	  { TEXNO::TITLE,              L"./Data/Images/title_select.png",        1U }, // �^�C�g��

   	  { TEXNO::TUTORIAL,           L"./Data/Images/Tutorial.png",       1U }, // �`���[�g���A��

	  { TEXNO::RESULT1,            L"./Data/Images/Result.png",       1U }, // ���U���g
	  { TEXNO::RESULT2,            L"./Data/Images/Result2.png",       1U }, 

	//{ TEXNO::GAMEOVER,         L"./Data/Images/.png",       1U }, //�Q�[���I�[�o�[

	  { TEXNO::GAME,              L"./Data/Images/stage_back.png",           1U },  // �w�i

		{ -1, nullptr }
};


//�}�N��
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // �摜�̐^�񒆂����S
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width),(height)   }  // �摜�̑��������S

//------< �v���C���[ >------------------
 // �e�N�X�`���̃C���f�b�N�X
 // �摜�؂�o���ʒu�i���A��j
 // �摜�T�C�Y
 // �摜�̒��S
//����

