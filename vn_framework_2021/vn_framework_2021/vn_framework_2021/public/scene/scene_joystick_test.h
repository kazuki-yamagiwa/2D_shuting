//--------------------------------------------------------------//
//	"scene_joystick_test.h"										//
//		�V�[���F�W���C�X�e�B�b�N�e�X�g							//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once

class SceneJoystickTest : public vnScene
{
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
