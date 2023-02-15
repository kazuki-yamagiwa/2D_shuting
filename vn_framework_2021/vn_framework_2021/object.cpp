#include "../../framework.h"
#include "../../framework/vn_environment.h"

#include "object.h"

//static�ϐ��̐錾
float vnObject::OffsetX = 0.0f;
float vnObject::OffsetY = 0.0f;

//�R���X�g���N�^
vnObject::vnObject(float x, float y, float width, float height, const WCHAR* texture_file, float left_u, float right_u, float top_v, float bottom_v) : vnSprite(x, y, width, height, texture_file, left_u, right_u, top_v, bottom_v)
{
	StageX = x;
	StageY = y;
}

//�f�X�g���N�^
vnObject::~vnObject()
{

}

//����
void vnObject::execute()
{
#if 0
	if (vnKeyboard::on(DIK_A) || vnKeyboard::on(DIK_LEFT))
	{	//���ړ�
		StageX -= 5;
	}
	if (vnKeyboard::on(DIK_D) || vnKeyboard::on(DIK_RIGHT))
	{	//�E�ړ�
		StageX += 5;
	}
#endif
	posX = StageX + OffsetX;
	posY = StageY + OffsetY;
}

//�I�t�Z�b�g�ʂ�ݒ�
void vnObject::setOffset(float ofsX, float ofsY)
{
	OffsetX = ofsX;
	OffsetY = ofsY;
}