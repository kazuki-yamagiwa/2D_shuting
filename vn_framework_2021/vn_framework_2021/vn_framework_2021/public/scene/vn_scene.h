//--------------------------------------------------------------//
//	"vn_scene.h"												//
//		�V�[�����N���X										//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once

#define vnOBJECT2D_MAX	(256)	//�o�^�ł���2D�I�u�W�F�N�g�̍ő吔

class vnScene
{
private:
	//�o�^�p�I�u�W�F�N�g�z��
	vnSprite* pObject2D_Array[vnOBJECT2D_MAX];

	static bool UpdateRenderPriority;	//�`��D�揇�ʂ��ύX���ꂽ�̂ŁA�\�[�g������K�v������

public:
	//�R���X�g���N�^
	vnScene();

	//�f�X�g���N�^
	virtual ~vnScene();
	
	//������
	virtual bool initialize()=0;

	//�I��
	virtual void terminate()=0;

	//����
	virtual void execute();

	//�`��
	virtual void render();

	//�`��D�揇�ʂ��ύX���ꂽ�̂ŁA�\�[�g������K�v������
	static void setUpdateRenderPriority();

	//2D�I�u�W�F�N�g�̓o�^(�z��̋󂫂ɓ����)
	bool registerObject(vnSprite* p);

	//2D�I�u�W�F�N�g�̔j��(�z�񂩂�폜)
	void deleteObject(vnSprite* p);
};