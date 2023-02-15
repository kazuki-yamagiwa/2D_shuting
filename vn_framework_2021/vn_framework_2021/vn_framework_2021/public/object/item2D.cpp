#include "../../framework.h"
#include "../../framework/vn_environment.h"

#include "item2D.h"

//�ÓI�����o�ϐ��̏�����
vnItem2D::stUV vnItem2D::defaultUV[eItemType::Max] =
{
	{0.0f,  0.0f},		//None,		//�^�C�v�Ȃ�
	{0.0f,  0.0f},		//Goal,		//�S�[���I�u�W�F�N�g
	{0.0f,  0.0f},		//Flag,		//���ԃI�u�W�F�N�g
	{0.25f, 0.0f},		//Heart,	//�񕜃I�u�W�F�N�g
	{0.5f,  0.0f},		//Clock,	//���v�I�u�W�F�N�g
	{0.0f,  0.25f},		//Key,		//���I�u�W�F�N�g
	{0.25f, 0.25f},		//Open,		//�싞��(�J)
	{0.5f,  0.25f},		//Close,	//�싞��(��)
};


//�R���X�g���N�^
vnItem2D::vnItem2D(float x, float y, float width, float height, const WCHAR* texture_file, float left_u, float right_u, float top_v, float bottom_v) : vnBlock2D(x, y, width, height, texture_file, left_u, right_u, top_v, bottom_v)
{
	type = eItemType::None;

	//�ėp�ϐ��̏�����
	pRelative = NULL;
	Value = 0.0f;
}

//�R���X�g���N�^(�I�[�o�[���[�h)
vnItem2D::vnItem2D(eItemType t, float x, float y, float width, float height) : vnBlock2D(x, y, width, height, L"data/image/item_icon.png", 0.0f, 1.0f, 0.0f, 1.0f)
{
	//�^�C�v�̐ݒ��UV�̐ݒ�
	setType(t);

	//�ėp�ϐ��̏�����
	pRelative = NULL;
	Value = 0.0f;
}


//�f�X�g���N�^
vnItem2D::~vnItem2D()
{
}

//�A�C�e���^�C�v�̎擾
vnItem2D::eItemType vnItem2D::getType()
{
	return type;
}

//�A�C�e���^�C�v�̐ݒ�
void vnItem2D::setType(eItemType t)
{
	type = t;

	//�^�C�v���̉摜��UV��ݒ�
	float su = defaultUV[type].u;	//Start(����)��u���W
	float sv = defaultUV[type].v;	//Start(�㑤)��v���W
	float du = 0.25f;	//��������u���W�̍���(4x4�̉摜)
	float dv = 0.25f;	//��������u���W�̍���(4x4�̉摜)
	//�|���S���̒��_��uv��ݒ�
	vtx[0].u = su;		vtx[0].v = sv;		//����
	vtx[1].u = su + dv;	vtx[1].v = sv;		//�E��
	vtx[2].u = su;		vtx[2].v = sv + dv;	//����
	vtx[3].u = su + dv;	vtx[3].v = sv + dv;	//�E��
}


//�֘A�A�C�e���̎擾
vnItem2D* vnItem2D::getRelative()
{
	return pRelative;
}

//�֘A�A�C�e���̐ݒ�
void vnItem2D::setRelative(vnItem2D* p)
{
	pRelative = p;
}

//�ėp���l�̎擾
float vnItem2D::getValue()
{
	return Value;
}

//�ėp���l�̐ݒ�
void vnItem2D::setValue(float v)
{
	Value = v;
}



//�v���C���[�ɐG�ꂽ���̐U�镑��
void vnItem2D::hit()
{
	switch (type)
	{
	case Goal:
		break;
	case Flag:
	case Heart:
	case Clock:
		setRenderEnable(false);
		break;
	}
}

