
#include"sprite_data.h"

GameLib::LoadTexture loadTexture[] =
{
	


		{ -1, nullptr }
};

#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // �摜�̐^�񒆂����S
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width),(height)   }  // �摜�̑��������S

//------< �v���C���[ >------------------
 // �e�N�X�`���̃C���f�b�N�X
 // �摜�؂�o���ʒu�i���A��j
 // �摜�T�C�Y
 // �摜�̒��S
//����

