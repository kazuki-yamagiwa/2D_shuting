#include "../../framework.h"
#include "../../framework/vn_environment.h"

//������
bool SceneSpriteTest::initialize()
{
	//�X�v���C�g�̍쐬
	pSprite = new vnSprite((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 512.0f, 512.0f, L"data/image/checker.png");

	pPoint[0] = new vnSprite((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 32.0f, 32.0f, 
		L"data/image/sample_texture.png",
		0.0f, 0.5f, 0.0f, 0.5f);

	pPoint[1] = new vnSprite((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 32.0f, 32.0f,
		L"data/image/sample_texture.png",
		0.5f, 1.0f, 0.0f, 0.5f);

	pPoint[2] = new vnSprite((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 32.0f, 32.0f,
		L"data/image/sample_texture.png",
		0.0f, 0.5f, 0.5f, 1.0f);

	pPoint[3] = new vnSprite((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 32.0f, 32.0f,
		L"data/image/sample_texture.png",
		0.5f, 1.0f, 0.5f, 1.0f);

	//�쐬�����X�v���C�g�����N���X(vnScene�N���X)�ɓo�^
	registerObject(pSprite);
	registerObject(pPoint[0]);
	registerObject(pPoint[1]);
	registerObject(pPoint[2]);
	registerObject(pPoint[3]);

	Cursor = 0;

	return true;
}

//�I��
void SceneSpriteTest::terminate()
{
	//�X�v���C�g�̍폜
	deleteObject(pSprite);
	deleteObject(pPoint[0]);
	deleteObject(pPoint[1]);
	deleteObject(pPoint[2]);
	deleteObject(pPoint[3]);
}

//�����֐�
void SceneSpriteTest::execute()
{
	float value_p = 1.0f;
	float value_s = 0.01f;
	float value_r = 1.0f * 3.141592f / 180.0f;

	if (vnKeyboard::trg(DIK_UP) && --Cursor<0)
	{
		Cursor = OperationMax-1;
	}
	else if (vnKeyboard::trg(DIK_DOWN) && ++Cursor >= OperationMax)
	{
		Cursor = 0;
	}
	else if (vnKeyboard::on(DIK_RIGHT))
	{
		switch (Cursor)
		{
		case PositionX:	pSprite->posX += value_p;	break;
		case PositionY:	pSprite->posY += value_p;	break;
		case ScaleX:	pSprite->scaleX += value_s;	break;
		case ScaleY:	pSprite->scaleY += value_s;	break;
		case Rotate:	pSprite->rot += value_r;	break;
		}
	}
	else if (vnKeyboard::on(DIK_LEFT))
	{
		switch (Cursor)
		{
		case PositionX:	pSprite->posX -= value_p;	break;
		case PositionY:	pSprite->posY -= value_p;	break;
		case ScaleX:	pSprite->scaleX -= value_s;	break;
		case ScaleY:	pSprite->scaleY -= value_s;	break;
		case Rotate:	pSprite->rot -= value_r;	break;
		}
	}
	else if (vnKeyboard::on(DIK_SPACE))
	{
		switch (Cursor)
		{
		case PositionX:	pSprite->posX = SCREEN_CENTER_X;	break;
		case PositionY:	pSprite->posY = SCREEN_CENTER_Y;	break;
		case ScaleX:	pSprite->scaleX = 1.0f;	break;
		case ScaleY:	pSprite->scaleY = 1.0f;	break;
		case Rotate:	pSprite->rot = 0.0f;	break;
		}
	}

	//�O�p�֐����g���ăX�v���C�g����]������

	//����_(x, y)���Ɖ�]��������̍��W(x', y')�́A�ȉ��̎��ŋ��߂���
	// x' = x * cos�� - y * sin��
	// y' = y * cos�� + x * sin��

	float centerX = pSprite->posX;	//��]�̒��S���W
	float centerY = pSprite->posY;	//��]�̒��S���W
	float v0x = -pSprite->sizeX * 0.5f * pSprite->scaleX;
	float v0y = -pSprite->sizeY * 0.5f * pSprite->scaleY;
	float v1x = +pSprite->sizeX * 0.5f * pSprite->scaleX;
	float v1y = -pSprite->sizeY * 0.5f * pSprite->scaleY;
	float v2x = -pSprite->sizeX * 0.5f * pSprite->scaleX;
	float v2y = +pSprite->sizeY * 0.5f * pSprite->scaleY;
	float v3x = +pSprite->sizeX * 0.5f * pSprite->scaleX;
	float v3y = +pSprite->sizeY * 0.5f * pSprite->scaleY;

	pPoint[0]->posX = v0x * cosf(pSprite->rot) - (v0y * sinf(pSprite->rot)) + centerX;
	pPoint[0]->posY = v0y * cosf(pSprite->rot) + (v0x * sinf(pSprite->rot)) + centerY;

	pPoint[1]->posX = v1x * cosf(pSprite->rot) - (v1y * sinf(pSprite->rot)) + centerX;
	pPoint[1]->posY = v1y * cosf(pSprite->rot) + (v1x * sinf(pSprite->rot)) + centerY;

	pPoint[2]->posX = v2x * cosf(pSprite->rot) - (v2y * sinf(pSprite->rot)) + centerX;
	pPoint[2]->posY = v2y * cosf(pSprite->rot) + (v2x * sinf(pSprite->rot)) + centerY;

	pPoint[3]->posX = v3x * cosf(pSprite->rot) - (v3y * sinf(pSprite->rot)) + centerX;
	pPoint[3]->posY = v3y * cosf(pSprite->rot) + (v3x * sinf(pSprite->rot)) + centerY;



	float x = 30.0f;
	float y = 10.0f;
	int line = 0;
	int interval = 16;
	vnFont::print(x-20.0f, (float)(y + Cursor * interval), L"��");
	vnFont::print(x, y + (float)(line++ * interval), L"Position X : %.3f", pSprite->posX);
	vnFont::print(x, y + (float)(line++ * interval), L"Position Y : %.3f", pSprite->posY);
	vnFont::print(x, y + (float)(line++ * interval), L"Scale X    : %.3f", pSprite->scaleX);
	vnFont::print(x, y + (float)(line++ * interval), L"Scale Y    : %.3f", pSprite->scaleY);
	vnFont::print(x, y + (float)(line++ * interval), L"Rotation   : %.3f", pSprite->rot / 3.1415192f * 180.0f);	//Radian��Degree�ɕϊ����ĕ\��

	vnScene::execute();
}

//�`��֐�
void SceneSpriteTest::render()
{
	//�V�[�����N���X�̕`��
	vnScene::render();
}
