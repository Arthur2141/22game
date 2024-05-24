
#include"sprite_data.h"

GameLib::LoadTexture loadTexture[] =
{
	


		{ -1, nullptr }
};

#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width),(height)   }  // 画像の足元が中心

//------< プレイヤー >------------------
 // テクスチャのインデックス
 // 画像切り出し位置（左、上）
 // 画像サイズ
 // 画像の中心
//歩き

