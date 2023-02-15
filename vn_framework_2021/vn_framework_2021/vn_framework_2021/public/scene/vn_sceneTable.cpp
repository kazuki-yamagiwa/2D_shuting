//--------------------------------------------------------------//
//	"vn_sceneTable.cpp"											//
//		�V�[���e�[�u��											//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#include "../../framework.h"
#include "../../framework/vn_environment.h"

//�N�����̃V�[��
eSceneTable initialScene = eSceneTable::Boot;
//���݂̃V�[��
eSceneTable currentScene = (eSceneTable)-1;
//�؂�ւ��\��̃V�[��
eSceneTable reserveScene = initialScene;
//�V�[���̃C���X�^���X
vnScene *pScene = NULL;


//�e�V�[���̖��O
WCHAR SceneName[(int)eSceneTable::SceneMax][32] =
{
	L"Boot",
	L"Action Test",
	L"Block Test",
	L"Sprite Test",
	L"Priority Test",
	L"Joystick Test",
	L"SE Test",
	L"Font Test",
};

//�V�[���؂�ւ��֐�(�\��)
void switchScene(eSceneTable scene)
{
	reserveScene = scene;
}

//�V�[���؂�ւ��֐�(������)
void switchScene()
{
	//�؂�ւ��\��̃`�F�b�N
	if(currentScene == reserveScene)
	{
		return;
	}
	
	//�V�[���폜
	deleteScene();

	//�V�[���̍쐬
	switch(reserveScene)
	{
	case eSceneTable::Boot:			pScene = new SceneBoot();			break;
	case eSceneTable::ActionTest:	pScene = new SceneActionTest();		break;
	case eSceneTable::BlockTest:	pScene = new SceneBlockTest();		break;
	case eSceneTable::SpriteTest:	pScene = new SceneSpriteTest();		break;
	case eSceneTable::PriorityTest:	pScene = new ScenePriorityTest();	break;
	case eSceneTable::JoystickTest:	pScene = new SceneJoystickTest();	break;
	case eSceneTable::SeTest:		pScene = new SceneSeTest();			break;
	case eSceneTable::FontTest:		pScene = new SceneFontTest();		break;
	}
	
	//���݂̃V�[����ݒ�
	currentScene = reserveScene;

	//�V�[���̏�����
	pScene->initialize();
}

//�V�[���폜
void deleteScene()
{
	if (pScene != NULL)
	{
		//�V�[���̏I��
		pScene->terminate();
		delete pScene;
		pScene = NULL;
	}
}
