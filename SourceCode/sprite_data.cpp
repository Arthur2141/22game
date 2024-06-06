
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
	  { TEXNO::TITLE,              L"./Data/Images/title_select.png",        1U }, // タイトル

   	  { TEXNO::TUTORIAL,           L"./Data/Images/Tutorial.png",       1U }, // チュートリアル

	  { TEXNO::RESULT1,            L"./Data/Images/Result.png",       1U }, // リザルト
	  { TEXNO::RESULT2,            L"./Data/Images/Result2.png",       1U }, 

	//{ TEXNO::GAMEOVER,         L"./Data/Images/.png",       1U }, //ゲームオーバー

	  { TEXNO::GAME,              L"./Data/Images/stage_back.png",           1U },  // 背景

		{ -1, nullptr }
};


//マクロ
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width),(height)   }  // 画像の足元が中心

//------< プレイヤー >------------------
 // テクスチャのインデックス
 // 画像切り出し位置（左、上）
 // 画像サイズ
 // 画像の中心
//歩き

