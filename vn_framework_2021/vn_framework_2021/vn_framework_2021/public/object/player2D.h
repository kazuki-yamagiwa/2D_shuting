//--------------------------------------------------------------//
//	"player2D.h"												//
//		�u���b�N���N���X										//
//													2021/11/11	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once	//������cpp�ŃC���N���[�h����Ă��A1��݂̂����C���N���[�h����Ȃ��悤�ɂ���
				//�C���N���[�h�K�[�h

class vnPlayer2D : public vnBlock2D
{
private:
	float move;			//���ړ��̑��x

	float velocity;		//���x(��������)
	float initVelocity;	//�����x

	float gravity;		//�d�͉����x

	bool jump;			//�W�����v��
	float jumpMove;		//�W�����v���̍��E�ړ���

	bool dash;			//�_�b�V����

	float animationCount;	//�A�j���[�V����(�摜�؂�ւ��̃J�E���^)

	int remain;			//�c�@��

public:
	//�R���X�g���N�^
	vnPlayer2D(float x, float y, float width, float height, const WCHAR* texture_file, float left_u = 0.0f, float right_u = 1.0f, float top_v = 0.0f, float bottom_v = 1.0f);

	//�f�X�g���N�^
	virtual ~vnPlayer2D();

	//����(���N���X�̊֐����I�[�o�[���C�h)
	virtual void execute();

	//�ĊJ(��������������)
	void restart(float x, float y);

	//�u���b�N�̏�ɏ����
	void landing();

	//�u���b�N�̉����瓖������
	void heading();

	//�c�@���̎擾
	int getRemain();

	//�c�@���̐ݒ�
	void setRemain(int value);

	//�Q�[���I�[�o�[
	void gameOver();

};
