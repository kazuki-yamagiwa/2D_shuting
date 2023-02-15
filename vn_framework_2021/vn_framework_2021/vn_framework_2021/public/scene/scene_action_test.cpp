#include "../../framework.h"
#include "../../framework/vn_environment.h"

//�I�u�W�F�N�g�̃^�C�v���Ƃ̕`��D�揇��
enum eRenderPriority
{
	BG = 0,
	Block = 100,
	Player = 200,
	UI = 500,
	Fade = 1000,
};

//�������֐�
bool SceneActionTest::initialize()
{
	//�z��̐����v�Z
	BlockMax = sizeof(pBlock) / sizeof(vnSprite*);

	//�z��̑S�v�f��NULL�N���A
	for (int i = 0; i < BlockMax; i++)
	{
		pBlock[i] = NULL;
	}

	//��ʉ��ɒn�ʗp�Ƀu���b�N����ׂ�
	for (int i = 0; i < 2560 / 64; i++)
	{
		if (i > 10 && i < 14)continue;

		if (i > 20 && i < 24)continue;

		pBlock[i] = new vnBlock2D(
			(float)(i*64+32), (float)(SCREEN_HEIGHT-32),
			64.0f, 64.0f,
			L"data/image/block.png",
			0.0f, 0.25f, 0.0f, 0.25f
		);
		pBlock[i]->setRenderPriority(eRenderPriority::Block);
		registerObject(pBlock[i]);
	}

	pBG = new vnBlock2D((float)SCREEN_WIDTH, (float)SCREEN_CENTER_Y,
		2560.0f, 720.0f,
		L"data/image/background.png");
	pBG->setRenderPriority(eRenderPriority::BG);
	registerObject(pBG);

	//�S�[���I�u�W�F�N�g�̍쐬
	pItem[0] = new vnItem2D(2560.0f - 256.0f, SCREEN_HEIGHT - 64.0f - 256.0f,
		512.0f, 512.0f,
		L"data/image/goal_object.png");
	pItem[0]->setRenderPriority(eRenderPriority::Block);
	registerObject(pItem[0]);

	pItem[0]->setType(vnItem2D::eItemType::Goal);

	//���ԃI�u�W�F�N�g�̍쐬
	pItem[1] = new vnItem2D(vnItem2D::eItemType::Flag, (float)(17 * 64 + 32), (float)(SCREEN_HEIGHT - 32 - 64));
	pItem[1]->setRenderPriority(eRenderPriority::Block);
	registerObject(pItem[1]);

	//�񕜃I�u�W�F�N�g�̍쐬
	pItem[2] = new vnItem2D(vnItem2D::eItemType::Heart, (float)(2 * 64 + 32), (float)(SCREEN_HEIGHT - 32 - 64 * 5));
	pItem[2]->setRenderPriority(eRenderPriority::Block);
	registerObject(pItem[2]);
	//�ėp���l�̐ݒ�(�񕜂���c�@��)
	pItem[2]->setValue(1.0f);

	//���v�I�u�W�F�N�g�̍쐬
	pItem[3] = new vnItem2D(vnItem2D::eItemType::Clock, (float)(8 * 64 + 32), (float)(SCREEN_HEIGHT - 32 - 64));
	pItem[3]->setRenderPriority(eRenderPriority::Block);
	registerObject(pItem[3]);
	//�ėp���l�̐ݒ�(�񕜂��鐧������)
	pItem[3]->setValue((float)(60 * 180));

	//���I�u�W�F�N�g�̍쐬
	pItem[4] = new vnItem2D(vnItem2D::eItemType::Key, (float)(5 * 64 + 32), (float)(SCREEN_HEIGHT - 32 - 64 * 3));
	pItem[4]->setRenderPriority(eRenderPriority::Block);
	registerObject(pItem[4]);

	//�싞���I�u�W�F�N�g�̍쐬
	pItem[5] = new vnItem2D(vnItem2D::eItemType::Close, (float)(17 * 64 + 32), (float)(SCREEN_HEIGHT - 32 - 64 * 4));
	pItem[5]->setRenderPriority(eRenderPriority::Block);
	registerObject(pItem[5]);

	//�֘A�A�C�e���̌��т�
	pItem[4]->setRelative(pItem[5]);	//���̎擾�ŁA�싞�� ���J

	//�Q�[���X�^�[�g���S�̍쐬
	pGameStart = new vnSprite(SCREEN_CENTER_X, SCREEN_CENTER_Y, 512.0f, 256.0f,
		L"data/image/game_start.png");
	pGameStart->setRenderPriority(eRenderPriority::UI);
	registerObject(pGameStart);


	//�Q�[���N���A���S�̍쐬
	pGameClear = new vnSprite(SCREEN_CENTER_X, SCREEN_CENTER_Y, 512.0f, 256.0f,
		L"data/image/game_clear.png");
	pGameClear->setRenderPriority(eRenderPriority::UI);
	registerObject(pGameClear);

	pGameClear->setRenderEnable(false);	//��\���ɂ���

	//�Q�[���I�[�o�[���S�̍쐬
	pGameOver = new vnSprite(SCREEN_CENTER_X, SCREEN_CENTER_Y, 512.0f, 256.0f,
		L"data/image/game_over.png");
	pGameOver->setRenderPriority(eRenderPriority::UI);
	registerObject(pGameOver);

	pGameOver->setRenderEnable(false);	//��\���ɂ���

	//�t�F�[�h�p�X�v���C�g�̍쐬
	pFade = new vnSprite(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH, SCREEN_HEIGHT, L"");
	pFade->setRenderPriority(eRenderPriority::Fade);
	registerObject(pFade);

	for (int i = 0; i < vnSprite::VertexNum; i++)
	{
		pFade->vtx[i].r = 0.0f;
		pFade->vtx[i].g = 0.0f;
		pFade->vtx[i].b = 0.0f;
		pFade->vtx[i].a = 1.0f;
	}



	////�u���b�N�̍쐬
	//pBlock[0] = new vnSprite(
	//	(float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y+100.0f,
	//	64.0f, 64.0f,
	//	L"data/image/block.png",
	//	0.0f, 0.25f, 0.0f, 0.25f
	//);
	//pBlock[1] = new vnSprite(
	//	(float)SCREEN_CENTER_X+100.0f, (float)SCREEN_CENTER_Y + 100.0f,
	//	64.0f, 64.0f,
	//	L"data/image/block.png",
	//	0.0f, 0.25f, 0.0f, 0.25f
	//);

	//�v���C���[�̏������W��ݒ�
	startX = 640.0f;
	startY = 500.0f;
	//�v���C���[�̍ĊJ���W��ݒ�
	respawnX = startX;
	respawnY = startY;

	//�v���C���[�I�u�W�F�N�g�̍쐬
	pPlayer = new vnPlayer2D(startX, startY,
		64.0f, 64.0f,
		L"data/image/face_icon.png",
		0.0f, 0.25f, 0.0f, 0.25f
	);

	//�쐬�����X�v���C�g�����N���X(vnScene�N���X)�ɓo�^
	pPlayer->setRenderPriority(eRenderPriority::Player);
	registerObject(pPlayer);
	//registerObject(pBlock[0]);
	//registerObject(pBlock[1]);

	//�t�F�[�h�C��/�A�E�g�̏��
	fadeCount = 0.0f;
	fadeInTime = 60.0f;
	fadeOutTime = 60.0f;

	//�X�e�[�W�̃X�N���[�����
	offsetX = 0.0f;
	offsetY = 0.0f;

	//�X�e�[�W�̐�������
	timeLimit = 60.0f;

	//�Q�[���̏������
	//gameState = eGameState::Start;
	gameState = eGameState::FadeOut;

	//�v���C���[�������Ȃ��悤�ɂ��Ă���
	pPlayer->setExecuteEnable(false);




	/*

	//�X�e�[�W�̏����o��(Visual Studio �̏o�̓p�l��)

	//�X�^�[�g�ʒu
	vnFont::output(L"StartPosition : (%.0f, %.0f)\n", startX, startY);
	//��������
	vnFont::output(L"TimeLimit : (%.0f)\n", timeLimit);

	//�u���b�N�̔z�u
	for (int i = 0, n=0; i < BlockMax; i++)
	{
		if (pBlock[i] == NULL)continue;

		vnFont::output(L"Block %d : (%.0f, %.0f)\n", n, pBlock[i]->posX, pBlock[i]->posY);
		n++;
	}

	//�A�C�e���̔z�u
	for (int i = 0, n = 0; i < 4; i++)
	{
		if (pItem[i] == NULL)continue;

		switch (pItem[i]->getType())
		{
		case vnItem2D::eItemType::None:
			vnFont::output(L"Item(None) %d : (%.0f, %.0f)\n", n, pItem[i]->posX, pItem[i]->posY);
			break;
		case vnItem2D::eItemType::Flag:
			vnFont::output(L"Item(Flag) %d : (%.0f, %.0f)\n", n, pItem[i]->posX, pItem[i]->posY);
			break;
		case vnItem2D::eItemType::Goal:
			vnFont::output(L"Item(Goal) %d : (%.0f, %.0f)\n", n, pItem[i]->posX, pItem[i]->posY);
			break;
		case vnItem2D::eItemType::Heart:
			vnFont::output(L"Item(Heart) %d : (%.0f, %.0f)\n", n, pItem[i]->posX, pItem[i]->posY);
			break;
		case vnItem2D::eItemType::Clock:
			vnFont::output(L"Item(Clock) %d : (%.0f, %.0f)\n", n, pItem[i]->posX, pItem[i]->posY);
			break;
		}
		n++;

	}
	*/
	
	return true;
}

//�I���֐�
void SceneActionTest::terminate()
{
	//�I�u�W�F�N�g�̍폜
	deleteObject(pPlayer);
	for (int i = 0; i < BlockMax; i++)
	{
		deleteObject(pBlock[i]);
	}
	deleteObject(pBG);
	for (int i = 0; i < 6; i++)
	{
		deleteObject(pItem[i]);
	}
	deleteObject(pGameClear);
	deleteObject(pGameStart);
	deleteObject(pGameOver);
	deleteObject(pFade);
}

//�����֐�
void SceneActionTest::execute()
{
	switch (gameState)
	{
	case eGameState::FadeOut:
		execute_fadeOut();
		vnFont::print(10, 10, L"GameState : FadeOut");
		break;
	case eGameState::Start:
		execute_start();
		vnFont::print(10, 10, L"GameState : Start");
		break;
	case eGameState::Play:
		execute_play();
		vnFont::print(10, 10, L"GameState : Play");
		break;
	case eGameState::Clear:
		execute_clear();
		vnFont::print(10, 10, L"GameState : Clear");
		break;
	case eGameState::Over:
		execute_over();
		vnFont::print(10, 10, L"GameState : Over");
		break;
	case eGameState::FadeIn:
		execute_fadeIn();
		vnFont::print(10, 10, L"GameState : FadeIn");
		break;
	}

	//�f�o�b�O���
	vnFont::print(10, 50, L"Player(Stage) : (%.3f, %.3f)", pPlayer->StageX, pPlayer->StageY);
	vnFont::print(10, 70, L"Player(Screen) : (%.3f, %.3f)", pPlayer->posX, pPlayer->posY);
	vnFont::print(10, 110, L"offsetX = %.3f", offsetX);
	vnFont::print(10, 150, L"Remain : %d", pPlayer->getRemain());
	vnFont::print(10, 190, L"Time Limit : %f", timeLimit);

	vnScene::execute();
}

void SceneActionTest::execute_fadeOut()
{
	fadeCount += 1.0f;

	float alpha = fadeCount / fadeOutTime;	//fadeCount(0�`60)��alpha(0�`1)
	alpha = 1.0f - alpha;	//alpha(0�`1)��alpha(1�`0)

	if (fadeCount >= fadeOutTime)
	{	//��莞�Ԃ��o�߂���
		gameState = eGameState::Start;

		fadeCount = 0.0f;

		alpha = 0.0f;

		pFade->setRenderEnable(false);
	}

	//�t�F�[�h�p�X�v���C�g�̓����x�̐ݒ�
	for (int i = 0; i < vnSprite::VertexNum; i++)
	{
		pFade->vtx[i].a = alpha;
	}
	/*
	* ���`���(Linear Interpolation : Lerp)
	* count : 0 �� 15   �� 30  �� 45   �� 60
	* alpha : 1 �� 0.75 �� 0.5 �� 0.25 �� 0
	*/

	vnFont::print(10, 230, L"Fade Out : %.1f / %.1f", fadeCount, fadeOutTime);
}

void SceneActionTest::execute_start()
{
	//Enter�L�[�������ƁAPlay��ԂɑJ�ڂ���
	if (vnKeyboard::trg(DIK_RETURN))
	{
		//�Q�[���̏�Ԃ�"�v���C"�ɂ���
		gameState = eGameState::Play;

		//�v���C���[��execute�����s��Ԃɂ��đ���ł���悤�ɂ���
		pPlayer->setExecuteEnable(true);

		//�Q�[���X�^�[�g�̃��S���\���ɂ���
		pGameStart->setRenderEnable(false);
	}
}

void SceneActionTest::execute_play()
{
	//�������Ԃ̌���
	timeLimit -= 1.0f;
	//���Ԃ������Ȃ�΃Q�[���I�[�o�[�ɂȂ�
	if (timeLimit <= 0.0f)
	{
		gameOver();
	}

	//�X�e�[�W�����痎������A�X�^�[�g�ʒu����ĊJ����
	if (pPlayer->StageY > SCREEN_HEIGHT + pPlayer->sizeY * 0.5f)
	{
		//�v���C���[�̎c�@�����擾
		int remain = pPlayer->getRemain();

		//�c�@����1���炷
		remain--;

		if (remain <= 0)
		{
			gameOver();
		}
		else
		{
			//���X�^�[�g�ʒu�ɖ߂��čĊJ
			pPlayer->restart(respawnX, respawnY);
		}
		//�v���C���[�̎c�@�����Đݒ�
		pPlayer->setRemain(remain);
	}
	//�X�e�[�W�̍��[�ɗ�����A����ȏ�s���Ȃ��悤�ɂ���
	if (pPlayer->StageX < 0.0f + pPlayer->sizeX * 0.5f)
	{
		pPlayer->StageX = 0.0f + pPlayer->sizeX * 0.5f;
	}
	//�X�e�[�W�̉E�[�ɗ�����A����ȏ�s���Ȃ��悤�ɂ���
	if (pPlayer->StageX > 2560.0f - pPlayer->sizeX * 0.5f)
	{
		pPlayer->StageX = 2560.0f - pPlayer->sizeX * 0.5f;
	}

	//�v���C���[�ƃu���b�N�̏Փ�
	for (int i = 0; i < BlockMax; i++)
	{
		if (pBlock[i] == NULL)continue;
		eCollideState hit = isCollide(pPlayer, pBlock[i]);
		switch (hit)
		{
		case FromLeft:	break;
		case FromRight:	break;
		case FromTop:
			pPlayer->landing();
			break;
		case FromBottom:
			pPlayer->heading();
			break;
		}
	}

	//�A�C�e���̏Փ˂ƃ^�C�v���Ƃ̐U�镑��
	for (int i = 0; i < 6; i++)
	{
		if (pItem[i]->isRenderEnable() == false)continue;

		eCollideState hit = isCollide(pPlayer, pItem[i], false);
		if (hit == eCollideState::None)continue;

		//enum eItemType
		//{
		//	None,	//�^�C�v�Ȃ�
		//	Goal,	//�S�[���I�u�W�F�N�g
		//	Flag,	//���ԃI�u�W�F�N�g
		//	Heart,	//�񕜃I�u�W�F�N�g
		//	Clock,	//���v�I�u�W�F�N�g
		//	Max,
		//};
		pItem[i]->hit();

		switch (pItem[i]->getType())
		{
		case vnItem2D::eItemType::Goal:
			//�Q�[���̏�Ԃ�"�N���A"�ɂ���
			gameState = eGameState::Clear;
			//�v���C���[��execute���~�߂āA�����Ȃ��悤�ɂ���
			pPlayer->setExecuteEnable(false);
			//�Q�[���N���A�̃��S��\������
			pGameClear->setRenderEnable(true);
			break;
		case vnItem2D::eItemType::Flag:
			//�ĊJ���W�𒆊ԃI�u�W�F�N�g�̍��W�ɍX�V����
			respawnX = pItem[i]->StageX;
			respawnY = pItem[i]->StageY;
			break;
		case vnItem2D::eItemType::Heart:
			//�v���C���[�̎c�@����1���₷
			pPlayer->setRemain(pPlayer->getRemain() + (int)pItem[i]->getValue());
			break;
		case vnItem2D::eItemType::Clock:
			//�������Ԃ𑝂₷
			timeLimit += pItem[i]->getValue();
			break;
		case vnItem2D::eItemType::Key:
		{	//�֘A�A�C�e�����ω�����(�싞�� ���J)
			vnItem2D* p = pItem[i]->getRelative();	//���A�C�e���Ɍ��т���ꂽ�싞���I�u�W�F�N�g���擾
			if (p == NULL)break;
			p->setType(vnItem2D::eItemType::Open);
			break;
		}
		}
	}


	//�v���C���[�ƃS�[���I�u�W�F�N�g�̏Փ�(�߂荞�݂̉����͂��Ȃ�)
	//eCollideState hit = isCollide(pPlayer, pItem[0], false);
	//if (hit != eCollideState::None)
	//{	//�Փ˂�����΁A�Q�[���̏�Ԃ�"�N���A"�ɂ���
	//	gameState = eGameState::Clear;

	//	//�v���C���[��execute���~�߂āA�����Ȃ��悤�ɂ���
	//	pPlayer->setExecuteEnable(false);

	//	//�Q�[���N���A�̃��S��\������
	//	pGameClear->setRenderEnable(true);
	//}

	////�v���C���[�ƒ��ԃI�u�W�F�N�g�̏Փ�(�߂荞�݂̉����͂��Ȃ�)
	//if (pItem[1]->isRenderEnable() == true)
	//{
	//	hit = isCollide(pPlayer, pItem[1], false);
	//	if (hit != eCollideState::None)
	//	{	//�ĊJ���W�𒆊ԃI�u�W�F�N�g�̍��W�ɍX�V����
	//		respawnX = pItem[1]->StageX;
	//		respawnY = pItem[1]->StageY;

	//		//�ēx�擾�ł��Ȃ��悤�ɔ�\���ɂ���
	//		pItem[1]->setRenderEnable(false);
	//	}
	//}

	////�v���C���[�Ɖ񕜃I�u�W�F�N�g�̏Փ�(�߂荞�݂̉����͂��Ȃ�)
	//if(pItem[2]->isRenderEnable() == true)
	//{
	//	hit = isCollide(pPlayer, pItem[2], false);
	//	if (hit != eCollideState::None)
	//	{	//�v���C���[�̎c�@����1���₷
	//		pPlayer->setRemain(pPlayer->getRemain()+1);

	//		//�ēx�擾�ł��Ȃ��悤�ɔ�\���ɂ���
	//		pItem[2]->setRenderEnable(false);
	//	}
	//}

	////�v���C���[�Ǝ��v�I�u�W�F�N�g�̏Փ�(�߂荞�݂̉����͂��Ȃ�)
	//if (pItem[3]->isRenderEnable() == true)
	//{
	//	hit = isCollide(pPlayer, pItem[3], false);
	//	if (hit != eCollideState::None)
	//	{	//�������Ԃ𑝂₷
	//		timeLimit += 60.0f*180.0f;

	//		//�ēx�擾�ł��Ȃ��悤�ɔ�\���ɂ���
	//		pItem[3]->setRenderEnable(false);
	//	}
	//}



	//�v���C���[�̃X�N���[�����W����ɉ�ʒ���(640)�ɕۂ��߂ɁA
	//�I�t�Z�b�g���v�Z
	offsetX = 640.0f - pPlayer->StageX;

	//�X�e�[�W���[�̏���
	if (offsetX > 0.0f)
	{
		offsetX = 0.0f;
	}
	//�X�e�[�W�E�[�̏���
	if (offsetX < -1280.0f)
	{
		offsetX = -1280.0f;
	}

	//�\�t�g�E�F�A���Z�b�g
	if (vnKeyboard::trg(DIK_R))
	{
		gameReset();
	}

	//�X�e�[�W���W����X�N���[�����W�֕ϊ�
	//��ʏ�̈ʒu = �X�e�[�W��̈ʒu + �I�t�Z�b�g��
	vnBlock2D::setOffset(offsetX, offsetY);

}

void SceneActionTest::execute_clear()
{
	//Enter�L�[�������ƁAStart��ԂɑJ�ڂ���
	if (vnKeyboard::trg(DIK_RETURN))
	{
		gameState = eGameState::FadeIn;

		pFade->setRenderEnable(true);
//		gameReset();
	}
}

void SceneActionTest::execute_over()
{
	//Enter�L�[�������ƁAStart��ԂɑJ�ڂ���
	if (vnKeyboard::trg(DIK_RETURN))
	{
		gameState = eGameState::FadeIn;

		pFade->setRenderEnable(true);
		//		gameReset();
	}
}

void SceneActionTest::execute_fadeIn()
{
	fadeCount += 1.0f;

	float alpha = fadeCount / fadeInTime;	//fadeCount(0�`60)��alpha(0�`1)

	if (fadeCount >= fadeInTime)
	{	//��莞�Ԃ��o�߂���
		gameState = eGameState::FadeOut;

		fadeCount = 0.0f;

		alpha = 1.0f;

		gameReset();
	}

	//�t�F�[�h�p�X�v���C�g�̓����x�̐ݒ�
	for (int i = 0; i < vnSprite::VertexNum; i++)
	{
		pFade->vtx[i].a = alpha;
	}

	vnFont::print(10, 230, L"Fade In : %.1f / %.1f", fadeCount, fadeInTime);
}



//�`��֐�
void SceneActionTest::render()
{
	vnScene::render();
}


//�Q�[���I�[�o�[�̏���
void SceneActionTest::gameOver()
{
	//�Q�[���̏�Ԃ�"�Q�[���I�[�o�["�ɂ���
	gameState = eGameState::Over;

	//�v���C���[��execute���~�߂āA�����Ȃ��悤�ɂ���
	pPlayer->setExecuteEnable(false);
	pPlayer->gameOver();

	//�Q�[���I�[�o�[�̃��S��\������
	pGameOver->setRenderEnable(true);
}

//�Q�[���̃��Z�b�g
void SceneActionTest::gameReset()
{
	//�Q�[���̏�Ԃ�"�t�F�[�h�A�E�g"�ɂ���
	gameState = eGameState::FadeOut;
	//�Q�[���X�^�[�g�̃��S��\������
	pGameStart->setRenderEnable(true);

	//�Q�[���I�[�o�[�̃��S���\���ɂ���
	pGameOver->setRenderEnable(false);

	//�Q�[���N���A�̃��S���\���ɂ���
	pGameClear->setRenderEnable(false);

	//��ʂ̃I�t�Z�b�g���Đݒ�
	offsetX = 640.0f - startX/*pPlayer->StageX*/;

	//�ĊJ���W���J�n���W�ɖ߂��Ă���
	respawnX = startX;
	respawnY = startY;

	//�X�e�[�W���W����X�N���[�����W�֕ϊ�
	//��ʏ�̈ʒu = �X�e�[�W��̈ʒu + �I�t�Z�b�g��
	vnBlock2D::setOffset(offsetX, offsetY);

	//�v���C���[�Ƀ��X�^�[�g����悤�`����
	//(��ɃI�t�Z�b�g�̐ݒ���ς܂��Ă���)
	pPlayer->restart(startX, startY);

	//�c�@����������Ԃɂ���
	pPlayer->setRemain(3);

	//�v���C���[��execute���~�߂āA�����Ȃ��悤�ɂ���
	pPlayer->setExecuteEnable(false);

	for (int i = 0; i < 6; i++)
	{
		pItem[i]->setRenderEnable(true);
	}

	//�싞���I�u�W�F�N�g�������Ԃɖ߂�
	pItem[5]->setType(vnItem2D::eItemType::Close);

	//���ԃI�u�W�F�N�g�𕜋A
//	pFlag->setRenderEnable(true);

	//�񕜃I�u�W�F�N�g�𕜋A
//	pHeart->setRenderEnable(true);

	//���v�I�u�W�F�N�g�𕜋A
//	pClock->setRenderEnable(true);

	//�������Ԃ̃��Z�b�g
	timeLimit = 60.0f;
}



//�X�v���C�g���m�̏Փ˂����o����
//�߂�l eCollideState : �Փ˂̏��
//����
//vnBlock2D *p1 : �Փ˂����o����1�ڂ̃I�u�W�F�N�g
//vnBlock2D *p2 : �Փ˂����o����2�ڂ̃I�u�W�F�N�g
//bool resolve : �Փ˂̉������s��(p1�𓮂����āAp2�͌Œ肷��)
SceneActionTest::eCollideState SceneActionTest::isCollide(vnBlock2D* p1, vnBlock2D* p2, bool resolve)
{
	//�����̃G���[�`�F�b�N
	if (p1 == NULL || p2 == NULL)
	{
		return eCollideState::None;
	}

	//�߂�l�p�̕ϐ�
	eCollideState hit = eCollideState::None;

	//�Փ˂̌��o
	float rx = 0.0f;	//�d�Ȃ��Ă��钷���`(Rectangle)�̕�
	float ry = 0.0f;	//�d�Ȃ��Ă��钷���`(Rectangle)�̍���

	//��(X)����

	//�X�v���C�g�̒��S���m�̍��W�̍���(differencial)
	float dx = fabsf(p1->StageX - p2->StageX);
	//2�̃X�v���C�g�̕�(����)���X�P�[���̍��v
	float sx = p1->sizeX * 0.5f * p1->scaleX + p2->sizeX * 0.5f * p2->scaleX;

	if (dx < sx)	//����������菬������Ή�(X)�����œ������Ă���
	{
		//�c(Y)����

		//�X�v���C�g�̒��S���m�̍��W�̍���(differencial)
		float dy = fabsf(p1->StageY - p2->StageY);
		//2�̃X�v���C�g�̍���(����)���X�P�[���̍��v
		float sy = p1->sizeY * 0.5f * p1->scaleY + p2->sizeY * 0.5f * p2->scaleY;

		if (dy < sy)	//������������菬������Ώc(Y)�����œ������Ă���
		{
			//�������Ă��Ȃ��Ƃ�����񂩂瓖�������Ƃ������ɏ���������
			hit = eCollideState::FromLeft;	

			//�d�Ȃ��Ă��钷���`�̃T�C�Y��ێ�
			rx = sx - dx;
			ry = sy - dy;

			vnFont::print(640, 40, L"r : %.3f, %.3f", rx, ry);
		}
	}

	//�Փ˂�����ꍇ�A�߂荞�݂���������
	//p1�𓮂����āAp2�͓������Ȃ�
	if (hit != eCollideState::None && resolve == true)
	{
		if (rx < ry)
		{	//�d�Ȃ����̈�(�����`)���c�������E����Փ�
			if (p1->StageX < p2->StageX)
			{	//p1��������Փ�
				vnFont::print(640, 60, L"from Left");
				p1->StageX -= rx;
				hit = eCollideState::FromLeft;
				//p2��UV�Ŗ���\��(��)
				//p2->vtx[0].u = 0.5f;	p2->vtx[0].v = 0.25f;
				//p2->vtx[1].u = 0.75f;	p2->vtx[1].v = 0.25f;
				//p2->vtx[2].u = 0.5f;	p2->vtx[2].v = 0.5f;
				//p2->vtx[3].u = 0.75f;	p2->vtx[3].v = 0.5f;
			}
			else
			{	//p1���E����Փ�
				vnFont::print(640, 60, L"from Right");
				p1->StageX += rx;
				hit = eCollideState::FromRight;
				//p2��UV�Ŗ���\��(��)
				//p2->vtx[0].u = 0.0f;	p2->vtx[0].v = 0.25f;
				//p2->vtx[1].u = 0.25f;	p2->vtx[1].v = 0.25f;
				//p2->vtx[2].u = 0.0f;	p2->vtx[2].v = 0.5f;
				//p2->vtx[3].u = 0.25f;	p2->vtx[3].v = 0.5f;
			}
		}
		else
		{	//�d�Ȃ����̈�(�����`)���������㉺����Փ�
			if (p1->StageY < p2->StageY)
			{	//p1���ォ��Փ�
				vnFont::print(640, 60, L"from Top");
				p1->StageY -= ry;
				hit = eCollideState::FromTop;
				//p2��UV�Ŗ���\��(��)
				//p2->vtx[0].u = 0.75f;	p2->vtx[0].v = 0.25f;
				//p2->vtx[1].u = 1.0f;	p2->vtx[1].v = 0.25f;
				//p2->vtx[2].u = 0.75f;	p2->vtx[2].v = 0.5f;
				//p2->vtx[3].u = 1.0f;	p2->vtx[3].v = 0.5f;
			}
			else
			{	//p1��������Փ�
				vnFont::print(640, 60, L"from Bottom");
				p1->StageY += ry;
				hit = eCollideState::FromBottom;
				//p2��UV�Ŗ���\��(��)
				//p2->vtx[0].u = 0.25f;	p2->vtx[0].v = 0.25f;
				//p2->vtx[1].u = 0.5f;	p2->vtx[1].v = 0.25f;
				//p2->vtx[2].u = 0.25f;	p2->vtx[2].v = 0.5f;
				//p2->vtx[3].u = 0.5f;	p2->vtx[3].v = 0.5f;
			}
		}
	}
	else
	{
		//p2��UV�Ŗ��n�̃u���b�N��\��
		//p2->vtx[0].u = 0.0f;	p2->vtx[0].v = 0.0f;
		//p2->vtx[1].u = 0.25f;	p2->vtx[1].v = 0.0f;
		//p2->vtx[2].u = 0.0f;	p2->vtx[2].v = 0.25f;
		//p2->vtx[3].u = 0.25f;	p2->vtx[3].v = 0.25f;
	}


	return hit;
}
