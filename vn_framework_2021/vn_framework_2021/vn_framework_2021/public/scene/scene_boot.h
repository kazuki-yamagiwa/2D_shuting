//--------------------------------------------------------------//
//	"scene_boot.h"												//
//		�V�[���F�N��/�V�[���Z���N�g								//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once

class SceneBoot : public vnScene
{
private:
	int Cursor;
	
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
