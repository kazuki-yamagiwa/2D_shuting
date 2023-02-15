#pragma once

class vnItem2D : public vnBlock2D
{
public:
	enum eItemType
	{
		None,	//�^�C�v�Ȃ�
		Goal,	//�S�[���I�u�W�F�N�g
		Flag,	//���ԃI�u�W�F�N�g
		Heart,	//�񕜃I�u�W�F�N�g
		Clock,	//���v�I�u�W�F�N�g
		Key,	//���I�u�W�F�N�g
		Open,	//�싞��(�J)
		Close,	//�싞��(��)
		Max,
	};

	struct stUV
	{
		float u;
		float v;
	};

private:
	eItemType type;

	//�ėp�I�ȕϐ�(�^�C�v���Ƃɖ������قȂ�)
	vnItem2D*	pRelative;	//���̃A�C�e���Ɋ֘A����A�C�e���̃|�C���^
	float		Value;		//�A�C�e�����ƂɌŗL�̒l

	//�A�C�e���^�C�v���Ƃ̋K���UV�l
	//static(�ÓI�ϐ�) : �v���O�������s���ɕς�邱�Ƃ̂Ȃ��l
	//�I�u�W�F�N�g���̂��쐬����/���Ȃ��ɂ�����炸�A��Ɉ�������݂���ϐ�
	//��static�ϐ���cpp�ł̍Đ錾���K�v(�ꏏ�ɏ�������)
	static stUV defaultUV[eItemType::Max];

public:
	//�R���X�g���N�^
	vnItem2D(float x, float y, float width, float height, const WCHAR* texture_file, float left_u = 0.0f, float right_u = 1.0f, float top_v = 0.0f, float bottom_v = 1.0f);

	vnItem2D(eItemType t, float x, float y, float width=64.0f, float height=64.0f);

	//�f�X�g���N�^
	virtual ~vnItem2D();

	//�A�C�e���^�C�v�̎擾
	eItemType getType();

	//�A�C�e���^�C�v�̐ݒ�
	void setType(eItemType t);

	//�֘A�A�C�e���̎擾
	vnItem2D* getRelative();

	//�֘A�A�C�e���̐ݒ�
	void setRelative(vnItem2D* p);

	//�ėp���l�̎擾
	float getValue();

	//�ėp���l�̐ݒ�
	void setValue(float v);

	//�v���C���[�ɐG�ꂽ���̐U�镑��
	void hit();
};