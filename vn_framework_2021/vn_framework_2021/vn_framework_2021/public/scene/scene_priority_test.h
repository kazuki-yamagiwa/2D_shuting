#pragma once

class ScenePriorityTest : public vnScene
{
private:
	vnSprite	*pSprite[256];	//�X�v���C�g�̔z��
	int			SpriteMax;		//�쐬�ł���X�v���C�g�̍ő吔
	int			SpriteNum;		//�쐬�����X�v���C�g�̐�

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
