#pragma once
#include"../GameLib/game_lib.h"
#include"../GameLib/obj2d_data.h"

void texture_draw(int texNo, const VECTOR2& pos, const VECTOR2& scale, const VECTOR2& texPos,
    const VECTOR2& texSize, const VECTOR2& center, float angle = 0.0f, const VECTOR4& color = { 1, 1, 1, 1 }, bool world = false);

enum TEXNO
{
    //タイトル
    TITLE,

    //チュートリアル
    TUTORIAL,

    //リザルト
    RESULT1,
    RESULT2,

    //ゲームオーバー
    GAMEOVER,

    //背景
    GAME,
};
extern GameLib::LoadTexture loadTexture[];


