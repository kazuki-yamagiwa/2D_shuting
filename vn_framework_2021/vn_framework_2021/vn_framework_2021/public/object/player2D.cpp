//--------------------------------------------------------------//
//	"player2D.cpp"												//
//		�u���b�N���N���X										//
//													2021/11/11	//
//														Ichii	//
//--------------------------------------------------------------//
#include "../../framework.h"
#include "../../framework/vn_environment.h"

#include "player2D.h"

//�R���X�g���N�^
vnPlayer2D::vnPlayer2D(float x, float y, float width, float height, const WCHAR* texture_file, float left_u, float right_u, float top_v, float bottom_v) : vnBlock2D(x, y, width, height, texture_file, left_u, right_u, top_v, bottom_v)
{
	//�e��ϐ��̏�����
	move = 5.0f;

	velocity = 0.0f;

	initVelocity = -20.0f;

	gravity = 0.5f;

	jump = true;
	jumpMove = 0.0f;

	dash = false;

	animationCount = 0.0f;

	remain = 3;
}

//�f�X�g���N�^
vnPlayer2D::~vnPlayer2D()
{
}

//����
void vnPlayer2D::execute()
{
	//�L�[���͂ɂ�鑀��
	float velocityX = 0.0f;
	dash = false;
	if (jump == false)
	{	//�W�����v���Ă��Ȃ��Ƃ�
		if (vnKeyboard::on(DIK_A) || vnKeyboard::on(DIK_LEFT))
		{	//���ړ�
			if (vnKeyboard::on(DIK_RSHIFT))
			{	//�_�b�V��
				StageX -= move * 2.0f;
				dash = true;
			}
			else
			{
				StageX -= move;
			}
			velocityX = -move;
		}
		if (vnKeyboard::on(DIK_D) || vnKeyboard::on(DIK_RIGHT))
		{	//�E�ړ�
			if (vnKeyboard::on(DIK_RSHIFT))
			{	//�_�b�V��
				StageX += move * 2.0f;
				dash = true;
			}
			else
			{
				StageX += move;
			}
			velocityX = move;
		}
	}
	else
	{	//�W�����v��
		if (vnKeyboard::on(DIK_A) || vnKeyboard::on(DIK_LEFT))
		{	//���ړ�
			StageX -= move * 0.5f;
			velocityX = -move * 0.5f;
		}
		if (vnKeyboard::on(DIK_D) || vnKeyboard::on(DIK_RIGHT))
		{	//�E�ړ�
			StageX += move * 0.5f;
			velocityX = move * 0.5f;
		}
	}
	if (vnKeyboard::trg(DIK_RETURN) && jump == false)
	{	//�W�����v�̏���
		velocity = initVelocity;	//����������ɔ�яオ���
		jump = true;			//�W�����v��Ԃɂ���
		jumpMove = velocityX;	//�W�����v�����u�Ԃ̉������̈ړ���
	}

	//���������̗�
	StageY += velocity;
	//���x�ɏd�͂������葱����
	velocity += gravity;



	//���N���X��execute���Ăяo��
	//�I�[�o�[���C�h���Ă���̂ŁA�����I�ɌĂяo���Ȃ��Ǝ��s����Ȃ�
	vnBlock2D::execute();	//�X�e�[�W���W���X�N���[�����W
}


//�ĊJ(��������������)
void vnPlayer2D::restart(float x, float y)
{
	//�v���C���[�̍��W���X�^�[�g�ʒu�ɂ���
	StageX = x;
	StageY = y;
	//���̑��̏������Z�b�g
	jump = true;
	velocity = 0.0f;

	//�Q�[���I�[�o�[�̉摜���f�t�H���g�ɖ߂�
	vtx[0].u = 0.00f;	vtx[0].v = 0.00f;
	vtx[1].u = 0.25f;	vtx[1].v = 0.00f;
	vtx[2].u = 0.00f;	vtx[2].v = 0.25f;
	vtx[3].u = 0.25f;	vtx[3].v = 0.25f;

	//�X�e�[�W���W���X�N���[�����W
	vnBlock2D::execute();
}

//�u���b�N�̏�ɏ����
void vnPlayer2D::landing()
{
	jump = false;
	velocity = 0.0f;
}

//�u���b�N�̉����瓖������
void vnPlayer2D::heading()
{
	velocity = 0.0f;
}

//�c�@���̎擾
int vnPlayer2D::getRemain()
{
	return remain;
}

//�c�@���̐ݒ�
void vnPlayer2D::setRemain(int value)
{
	remain = value;
}

//�Q�[���I�[�o�[
void vnPlayer2D::gameOver()
{
	vtx[0].u = 0.75f;	vtx[0].v = 0.25f;
	vtx[1].u = 1.00f;	vtx[1].v = 0.25f;
	vtx[2].u = 0.75f;	vtx[2].v = 0.50f;
	vtx[3].u = 1.00f;	vtx[3].v = 0.50f;
}
