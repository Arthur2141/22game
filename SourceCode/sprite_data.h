#pragma once
#include"../GameLib/game_lib.h"
#include"../GameLib/obj2d_data.h"

void texture_draw(int texNo, const VECTOR2& pos, const VECTOR2& scale, const VECTOR2& texPos,
    const VECTOR2& texSize, const VECTOR2& center, float angle = 0.0f, const VECTOR4& color = { 1, 1, 1, 1 }, bool world = false);

enum TEXNO
{
    //�^�C�g��
    TITLE,

    //�`���[�g���A��
    TUTORIAL,

    //���U���g
    RESULT1,
    RESULT2,

    //�Q�[���I�[�o�[
    GAMEOVER,

    //�w�i
    GAME,
};
extern GameLib::LoadTexture loadTexture[];


