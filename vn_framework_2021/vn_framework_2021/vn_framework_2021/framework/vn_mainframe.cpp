//--------------------------------------------------------------//
//	"vn_mainframe.cpp"											//
//		���C���t���[��											//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#include "../framework.h"
#include "vn_environment.h"

//�N�����̃V�[��
extern eSceneTable initialScene;
//�V�[���̃C���X�^���X
extern vnScene* pScene;

//�Œ�t���[�����[�g�̂��߂̃p�t�H�[�}���X�J�E���^�[
bool performanceCounter;
LARGE_INTEGER freq, startCount, finishCount;
float count;

//�ÓI�ϐ�
float vnMainFrame::clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };	//��ʂ̃N���A�J���[

//���C���t���[���̏�����
bool vnMainFrame::initialize(void *hWnd, void *hInst)
{
	//�p�t�H�[�}���X�J�E���^�̏�����
	memset(&freq, 0, sizeof(freq));
	memset(&startCount, 0, sizeof(startCount));
	memset(&finishCount, 0, sizeof(finishCount));
	count = 0.0f;

	performanceCounter = QueryPerformanceFrequency(&freq);

	//�e��R���|�[�l���g�̏�����
	vnDirect3D::initialize(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);

	vnDirect2D::initialize(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);

	vnDirectInput::initialize(hInst);

	vnDirectSound::initialize(hWnd);

	vnShader::initialize();

	vnFont::initialize();

	vnSprite::initializeCommon();

	//�V�[���̍쐬
	switchScene();

	return true;
}

//���C���t���[���̏I��
void vnMainFrame::terminate()
{
	//�V�[���̍폜
	deleteScene();

	//�e��R���|�[�l���g�̏I��
	vnSprite::terminateCommon();

	vnFont::terminate();

	vnShader::terminate();

	vnDirectSound::terminate();

	vnDirectInput::terminate();

	vnDirect2D::terminate();

	vnDirect3D::terminate();
}

//���C���t���[���̏���
void vnMainFrame::execute()
{
	if (performanceCounter)
	{	//�t���[���̊J�n���Ԃ��擾
		QueryPerformanceCounter(&startCount);
	}

	//���͊Ǘ�
	vnDirectInput::KeyManager();

	//�ʏ폈���J�n
	pScene->execute();
	//�ʏ폈���I��

	//HOME�{�^���ŋN�����̃X�e�[�W�ɖ߂�B
	if (vnKeyboard::trg(DIK_HOME))
	{
		switchScene(initialScene);
	}

	//�����_�[�^�[�Q�b�g���N���A
	vnDirect3D::clear();

	//�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT	Viewport;
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
	Viewport.Width = (float)SCREEN_WIDTH;
	Viewport.Height = (float)SCREEN_HEIGHT;
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	vnDirect3D::getDeviceContext()->RSSetViewports(1, &Viewport);

	//�`�揈���J�n
	pScene->render();

	vnDirect2D::render();
	//�`�揈���I��

	//�V�[���̐؂�ւ�
	switchScene();

	if (performanceCounter)
	{	//�t���[���̏I�����Ԃ��擾
		static float frame_msec = 1.0f / 60.0f;
		QueryPerformanceCounter(&finishCount);
		count = ((float)(finishCount.QuadPart - startCount.QuadPart) / (float)freq.QuadPart);

		if (count < frame_msec)
		{	//1/60�b���o�܂ő҂�
			DWORD wait = (DWORD)((frame_msec - count) * 1000.0f - 0.5f);
			timeBeginPeriod(1);
			Sleep(wait);
			timeEndPeriod(1);
		}
	}

	//�v���[���e�[�V����
	vnDirect3D::present();
}
