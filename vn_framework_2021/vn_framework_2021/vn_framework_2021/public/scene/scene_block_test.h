#pragma once

class SceneBlockTest : public vnScene
{
private:
	vnSprite	*pPlayer;	//�v���C���[
	vnSprite	*pSprite;	//�u���b�N

	//����̎��
	enum eOperation
	{
		PositionX,
		PositionY,
		ScaleX,
		ScaleY,
		OperationMax,
	};

	int	Cursor;

	//�X�v���C�g���m�̏Փ˂����o����
	//�߂�l true : �Փ˂��Ă���Afalse : �Փ˂��Ă��Ȃ�
	//����
	//vnSprite *p1 : �Փ˂����o����1�ڂ̃X�v���C�g
	//vnSprite *p2 : �Փ˂����o����2�ڂ̃X�v���C�g
	//bool resolve : �Փ˂̉������s��(p1�𓮂����āAp2�͌Œ肷��)
	bool isCollide(vnSprite* p1, vnSprite* p2, bool resolve=true);
	
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
