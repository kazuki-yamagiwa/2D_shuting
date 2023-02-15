#pragma once

#include "../object/block2D.h"
#include "../object/player2D.h"
#include "../object/item2D.h"

class SceneActionTest : public vnScene
{
private:
	//�Q�[���̏��
	enum eGameState
	{
		FadeOut,//�t�F�[�h�A�E�g
		Start,	//�X�^�[�g
		Play,	//�v���C��
		Clear,	//�Q�[���N���A
		Over,	//�Q�[���I�[�o�[
		FadeIn,	//�t�F�[�h�C��
	};
	eGameState gameState;

	vnSprite* pGameStart;	//�Q�[���X�^�[�g�̃��S
	vnSprite* pGameClear;	//�Q�[���N���A�̃��S
	vnSprite* pGameOver;	//�Q�[���I�[�o�[�̃��S

	vnSprite* pFade;		//�t�F�[�h�p�X�v���C�g

	vnBlock2D* pBG;			//�w�i�摜

	//�t�F�[�h�C��/�A�E�g�̏��
	float fadeCount;	//�t�F�[�h���n�܂��Ă���̎���
	float fadeInTime;	//�t�F�[�h�C���ɗv���鎞��
	float fadeOutTime;	//�t�F�[�h�A�E�g�ɗv���鎞��
	
	//�X�e�[�W�̃X�N���[�����
	float offsetX;
	float offsetY;

	//�X�e�[�W�̐�������(�t���[��)
	float timeLimit;

	vnBlock2D* pBlock[64];	//�u���b�N�I�u�W�F�N�g
	int	BlockMax;			//�u���b�N�z��̐�

	vnPlayer2D* pPlayer;	//�v���C���[�I�u�W�F�N�g

	vnItem2D* pItem[6];		//�A�C�e���I�u�W�F�N�g�̔z��

	//vnItem2D* pGoal;		//�S�[���I�u�W�F�N�g

	//vnItem2D* pFlag;		//���ԃI�u�W�F�N�g

	//vnItem2D* pHeart;		//�񕜃I�u�W�F�N�g(�c�@���A�b�v)

	//vnItem2D* pClock;		//���v�I�u�W�F�N�g(�������ԑ���)

	float startX;		//�v���C���[�̏������W(X)
	float startY;		//�v���C���[�̏������W(Y)
	float respawnX;		//�v���C���[�̍ĊJ���W(X)
	float respawnY;		//�v���C���[�̍ĊJ���W(Y)

	enum eCollideState	//�Փ˂̏�Ԃ�\���񋓎q(enum)
	{
		None,		//�Փ˂��Ă��Ȃ�
		FromLeft,	//��������Փ�
		FromRight,	//�E������Փ�
		FromTop,	//�㑤����Փ�
		FromBottom,	//��������Փ�
	};
	//�X�v���C�g���m�̏Փ˂����o����
	//�߂�l eCollideState : �Փ˂̏��
	//����
	//vnBlock2D *p1 : �Փ˂����o����1�ڂ̃I�u�W�F�N�g
	//vnBlock2D *p2 : �Փ˂����o����2�ڂ̃I�u�W�F�N�g
	//bool resolve : �Փ˂̉������s��(p1�𓮂����āAp2�͌Œ肷��)
	eCollideState isCollide(vnBlock2D* p1, vnBlock2D* p2, bool resolve = true);

	//�Q�[���̏�Ԃ��Ƃ�execute�֐�
	void execute_fadeOut();
	void execute_start();
	void execute_play();
	void execute_clear();
	void execute_over();
	void execute_fadeIn();

	//�Q�[���I�[�o�[�̏���
	void gameOver();

	//�Q�[���̃��Z�b�g
	void gameReset();

public:
	//������
	bool initialize();
	//�I��
	void terminate();

	//����
	void execute();
	//�`��
	void render();
};
