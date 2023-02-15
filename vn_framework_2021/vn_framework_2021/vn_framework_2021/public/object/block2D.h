//--------------------------------------------------------------//
//	"block2D.h"													//
//		�u���b�N���N���X										//
//													2021/11/09	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once	//������cpp�ŃC���N���[�h����Ă��A1��݂̂����C���N���[�h����Ȃ��悤�ɂ���
				//�C���N���[�h�K�[�h

class vnBlock2D : public vnSprite
{
//protected:	//���g�ƁA�h����̃N���X�̂ݎQ�Ɖ\
public:
	float	StageX;	//�X�e�[�W���ł̍��W(X)
	float	StageY;	//�X�e�[�W���ł̍��W(Y)

private:	//���g�̂ݎQ�Ɖ\

	//��static�����āA�SvnBlock2D�I�u�W�F�N�g�ɋ��L���������̕ϐ��ɂ���
	static float	OffsetX;	//�X�e�[�W�̃X�N���[����(X)
	static float	OffsetY;	//�X�e�[�W�̃X�N���[����(Y)

public:	//�ǂ�����ł��Q�Ɖ\

	//�R���X�g���N�^
	vnBlock2D(float x, float y, float width, float height, const WCHAR* texture_file, float left_u = 0.0f, float right_u = 1.0f, float top_v = 0.0f, float bottom_v = 1.0f);

	//�f�X�g���N�^
	virtual ~vnBlock2D();

	//����(���N���X�̊֐����I�[�o�[���C�h)
	virtual void execute();

	//�I�t�Z�b�g�ʂ�ݒ肷��֐�(��static�ϐ��ɐݒ肷��̂ŁA���̊֐����g��static�ɂ���)
	static void setOffset(float ofsX, float ofsY);

};
