//--------------------------------------------------------------//
//	"scene_se_test.h"											//
//		�V�[���FSE�e�X�g										//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once

class SceneSeTest : public vnScene
{
private:

	//�t�@�C���̐�
	int fileNum;

	//wav�t�@�C����炷�I�u�W�F�N�g(1�t�@�C���A1�� = 1�I�u�W�F�N�g)
	vnSound	**pSound;
	
public:
	//������
	bool initialize();

	//�I��
	void terminate();

	//����
	virtual void execute();

	//�`��
	virtual void render();
};
