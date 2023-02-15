#include "../../framework.h"
#include "../../framework/vn_environment.h"

//�������֐�
bool ScenePriorityTest::initialize()
{
	//�쐬�ł���X�v���C�g�̍ő吔(�z��̐�)
	//�z��S�̂̃o�C�g����v�f��̃o�C�g���Ŋ���
	SpriteMax = sizeof(pSprite) / sizeof(vnSprite*);

	//�|�C���^�̏�����(NULL�N���A)
	for (int i = 0; i < SpriteMax; i++)
	{
		pSprite[i] = NULL;
	}

	//�쐬�����X�v���C�g�̐�
	SpriteNum = 0;

	return true;
}

//�I���֐�
void ScenePriorityTest::terminate()
{
	//���������X�v���C�g�̍폜
	for (int i = 0; i < SpriteMax; i++)
	{
		if (pSprite[i] == NULL)continue;
		deleteObject(pSprite[i]);
	}
}

//�����֐�
void ScenePriorityTest::execute()
{
	vnFont::print(10, 10, L"Priority Test : %d", SpriteNum);
	/*
	
	�}�E�X�����N���b�N�����Ƃ���ɁA�X�v���C�g�����������B
	�X�v���C�g�̉摜�́A�����_����0�`9�̐����̃e�N�X�`����������B

	[�ǉ��d�l]�h���b�O�ł���ňړ���������A�E�N���b�N�ŏ�������...
	*/

	//�}�E�X�̍��N���b�N
	if (vnMouse::trg() == true)
	{
		int disp = rand() % 10;	//0�`9�܂ł̃����_���l�𓾂�

		//0�`9�̉摜�ɑΉ�����uv���v�Z
		float interval_u = 1.0f / 4.0f;	//�摜���Ƃ̊Ԋu(u����)
		float interval_v = 1.0f / 4.0f;	//�摜���Ƃ̊Ԋu(v����)
		float start_u = (float)(disp % 4) * interval_u;	//�ݒ肵����u�l�̍����̒l
		float start_v = (float)(disp / 4) * interval_v;	//�ݒ肵����v�l�̏㑤�̒l

		//�}�E�X�J�[�\���̍��W���擾
		float mx = (float)vnMouse::getX();
		float my = (float)vnMouse::getY();
		//�X�v���C�g�𐶐�
		pSprite[SpriteNum] = new vnSprite(mx, my, 64.0f, 64.0f, 
			L"data/image/number_icon.png", 
			start_u, start_u+interval_u, start_v, start_v+interval_v);
		//�`��D�揇�ʂ̐ݒ�
		pSprite[SpriteNum]->setRenderPriority(10-disp);
		
		//�쐬�����X�v���C�g��o�^
		registerObject(pSprite[SpriteNum]);
		
		//�X�v���C�g�̐���1���₷(increment)
		SpriteNum++;
	}

	vnScene::execute();
}

//�`��֐�
void ScenePriorityTest::render()
{
	vnScene::render();
}
