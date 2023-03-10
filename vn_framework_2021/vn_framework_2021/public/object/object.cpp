#include "../../framework.h"
#include "../../framework/vn_environment.h"

#include "object.h"


//static変数の宣言
float vnBlock2D::OffsetX = 0.0f;
float vnBlock2D::OffsetY = 0.0f;

//コンストラクタ
vnBlock2D::vnBlock2D(float x, float y, float width, float height, const WCHAR* texture_file, float left_u, float right_u, float top_v, float bottom_v) : vnSprite(x, y, width, height, texture_file, left_u, right_u, top_v, bottom_v)
{
	StageX = x;
	StageY = y;
}

//デストラクタ
vnBlock2D::~vnBlock2D()
{

}

//処理
void vnBlock2D::execute()
{
		if (vnKeyboard::on(DIK_A) || vnKeyboard::on(DIK_LEFT))
		{	//左移動
				StageX -= 5;
		}
		if (vnKeyboard::on(DIK_D) || vnKeyboard::on(DIK_RIGHT))
		{	//右移動
				StageX += 5;
		}

	posX = StageX + OffsetX;
	posY = StageY + OffsetY;
}

//オフセット量を設定
void vnBlock2D::setOffset(float ofsX, float ofsY)
{
	OffsetX = ofsX;
	OffsetY = ofsY;
}