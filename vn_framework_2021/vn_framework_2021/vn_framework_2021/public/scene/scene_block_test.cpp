#include "../../framework.h"
#include "../../framework/vn_environment.h"

//������
bool SceneBlockTest::initialize()
{
	//�v���C���[�̍쐬
	pPlayer = new vnSprite(
		(float)SCREEN_CENTER_X/2, (float)SCREEN_CENTER_Y,
		64.0f, 64.0f,
		L"data/image/block.png",
		0.0f, 0.25f, 0.0f, 0.25f
	);
	//�u���b�N�̍쐬
	pSprite = new vnSprite(
		(float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 
		64.0f, 64.0f, 
		L"data/image/block.png",
		0.0f, 0.25f, 0.0f, 0.25f
	);

	//�쐬�����X�v���C�g�����N���X(vnScene�N���X)�ɓo�^
	registerObject(pPlayer);
	registerObject(pSprite);

	Cursor = 0;

	return true;
}

//�I��
void SceneBlockTest::terminate()
{
	//�X�v���C�g�̍폜
	deleteObject(pPlayer);
	deleteObject(pSprite);
}

//�����֐�
void SceneBlockTest::execute()
{
	float value_p = 1.0f;
	float value_s = 0.01f;
	float value_r = 1.0f * 3.141592f / 180.0f;

	//�v���C���[�̑���
	if (vnKeyboard::on(DIK_W))
	{
		pPlayer->posY -= value_p;
	}
	if (vnKeyboard::on(DIK_S))
	{
		pPlayer->posY += value_p;
	}
	if (vnKeyboard::on(DIK_A))
	{
		pPlayer->posX -= value_p;
	}
	if (vnKeyboard::on(DIK_D))
	{
		pPlayer->posX += value_p;
	}

	//�u���b�N�̑���
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
		}
	}

	//�X�v���C�g�̏Փ˂����o����(�߂荞�݂̉������s��)
	bool hit = isCollide(pPlayer, pSprite);

	//���ʂ̃f�o�b�O�\��
	if (hit == true)
	{
		vnFont::print(640, 20, L"hit : true");
	}
	else
	{
		vnFont::print(640, 20, L"hit : false");
	}


	float x = 30.0f;
	float y = 10.0f;
	int line = 0;
	int interval = 16;
	vnFont::print(x-20.0f, (float)(y + Cursor * interval), L"��");
	vnFont::print(x, y + (float)(line++ * interval), L"Position X : %.3f", pSprite->posX);
	vnFont::print(x, y + (float)(line++ * interval), L"Position Y : %.3f", pSprite->posY);
	vnFont::print(x, y + (float)(line++ * interval), L"Scale X    : %.3f", pSprite->scaleX);
	vnFont::print(x, y + (float)(line++ * interval), L"Scale Y    : %.3f", pSprite->scaleY);

	vnScene::execute();
}

//�`��֐�
void SceneBlockTest::render()
{
	//�V�[�����N���X�̕`��
	vnScene::render();
}



//�X�v���C�g���m�̏Փ˂����o����
//�߂�l true : �Փ˂��Ă���Afalse : �Փ˂��Ă��Ȃ�
//����
//vnSprite *p1 : �Փ˂����o����1�ڂ̃X�v���C�g
//vnSprite *p2 : �Փ˂����o����2�ڂ̃X�v���C�g
//bool resolve : �Փ˂̉������s��(p1�𓮂����āAp2�͌Œ肷��)
bool SceneBlockTest::isCollide(vnSprite* p1, vnSprite* p2, bool resolve)
{
	//�����̃G���[�`�F�b�N
	if (p1 == NULL || p2 == NULL)
	{
		return false;
	}

	//�߂�l�p�̕ϐ�
	bool hit = false;

	//�Փ˂̌��o
	float rx = 0.0f;	//�d�Ȃ��Ă��钷���`(Rectangle)�̕�
	float ry = 0.0f;	//�d�Ȃ��Ă��钷���`(Rectangle)�̍���

	//��(X)����

	//�X�v���C�g�̒��S���m�̍��W�̍���(differencial)
	float dx = fabsf(p1->posX - p2->posX);
	//2�̃X�v���C�g�̕�(����)���X�P�[���̍��v
	float sx = p1->sizeX * 0.5f * p1->scaleX + p2->sizeX * 0.5f * p2->scaleX;

	if (dx < sx)	//����������菬������Ή�(X)�����œ������Ă���
	{
		//�c(Y)����

		//�X�v���C�g�̒��S���m�̍��W�̍���(differencial)
		float dy = fabsf(p1->posY - p2->posY);
		//2�̃X�v���C�g�̍���(����)���X�P�[���̍��v
		float sy = p1->sizeY * 0.5f * p1->scaleY + p2->sizeY * 0.5f * p2->scaleY;

		if (dy < sy)	//������������菬������Ώc(Y)�����œ������Ă���
		{
			hit = true;

			//�d�Ȃ��Ă��钷���`�̃T�C�Y��ێ�
			rx = sx - dx;
			ry = sy - dy;

			vnFont::print(640, 40, L"r : %.3f, %.3f", rx, ry);
		}
	}

	//�Փ˂�����ꍇ�A�߂荞�݂���������
	//p1�𓮂����āAp2�͓������Ȃ�
	if (hit == true && resolve == true)
	{
		if (rx < ry)
		{	//�d�Ȃ����̈�(�����`)���c�������E����Փ�
			if (p1->posX < p2->posX)
			{	//p1��������Փ�
				vnFont::print(640, 60, L"from Left");
				p1->posX -= rx;
				//p2��UV�Ŗ���\��(��)
				p2->vtx[0].u = 0.5f;	p2->vtx[0].v = 0.25f;
				p2->vtx[1].u = 0.75f;	p2->vtx[1].v = 0.25f;
				p2->vtx[2].u = 0.5f;	p2->vtx[2].v = 0.5f;
				p2->vtx[3].u = 0.75f;	p2->vtx[3].v = 0.5f;
			}
			else
			{	//p1���E����Փ�
				vnFont::print(640, 60, L"from Right");
				p1->posX += rx;
				//p2��UV�Ŗ���\��(��)
				p2->vtx[0].u = 0.0f;	p2->vtx[0].v = 0.25f;
				p2->vtx[1].u = 0.25f;	p2->vtx[1].v = 0.25f;
				p2->vtx[2].u = 0.0f;	p2->vtx[2].v = 0.5f;
				p2->vtx[3].u = 0.25f;	p2->vtx[3].v = 0.5f;
			}
		}
		else
		{	//�d�Ȃ����̈�(�����`)���������㉺����Փ�
			if (p1->posY < p2->posY)
			{	//p1���ォ��Փ�
				vnFont::print(640, 60, L"from Top");
				p1->posY -= ry;
				//p2��UV�Ŗ���\��(��)
				p2->vtx[0].u = 0.75f;	p2->vtx[0].v = 0.25f;
				p2->vtx[1].u = 1.0f;	p2->vtx[1].v = 0.25f;
				p2->vtx[2].u = 0.75f;	p2->vtx[2].v = 0.5f;
				p2->vtx[3].u = 1.0f;	p2->vtx[3].v = 0.5f;
			}
			else
			{	//p1��������Փ�
				vnFont::print(640, 60, L"from Bottom");
				p1->posY += ry;
				//p2��UV�Ŗ���\��(��)
				p2->vtx[0].u = 0.25f;	p2->vtx[0].v = 0.25f;
				p2->vtx[1].u = 0.5f;	p2->vtx[1].v = 0.25f;
				p2->vtx[2].u = 0.25f;	p2->vtx[2].v = 0.5f;
				p2->vtx[3].u = 0.5f;	p2->vtx[3].v = 0.5f;
			}
		}
	}
	else
	{
		//p2��UV�Ŗ��n�̃u���b�N��\��
		p2->vtx[0].u = 0.0f;	p2->vtx[0].v = 0.0f;
		p2->vtx[1].u = 0.25f;	p2->vtx[1].v = 0.0f;
		p2->vtx[2].u = 0.0f;	p2->vtx[2].v = 0.25f;
		p2->vtx[3].u = 0.25f;	p2->vtx[3].v = 0.25f;
	}


	return hit;
}
