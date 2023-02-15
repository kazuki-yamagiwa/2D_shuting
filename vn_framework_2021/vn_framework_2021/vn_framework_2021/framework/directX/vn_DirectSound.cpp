//--------------------------------------------------------------//
//	"vn_DirectSound.cpp"										//
//		DirectSound�Ǘ�											//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#include "../../framework.h"
#include "../vn_environment.h"

IDirectSound8 *vnDirectSound::pDS8=NULL;
LPDIRECTSOUNDBUFFER vnDirectSound::lpPrimary=NULL;

int vnDirectSound::initialize(void *hdl)
{
	HRESULT ret;
	//�T�E���h�f�o�C�X�쐬
	DirectSoundCreate8(NULL, &pDS8, NULL);
	
	//�������x���ݒ�
	pDS8->SetCooperativeLevel((HWND)hdl, DSSCL_NORMAL); 
	WAVEFORMATEX wf;
	
    // �v���C�}���T�E���h�o�b�t�@�̍쐬
    DSBUFFERDESC dsdesc;
    ZeroMemory( &dsdesc,sizeof(DSBUFFERDESC) );
    dsdesc.dwSize = sizeof( DSBUFFERDESC );
    dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;
    dsdesc.dwBufferBytes = 0;
    dsdesc.lpwfxFormat = NULL;
    ret = pDS8->CreateSoundBuffer( &dsdesc,&lpPrimary,NULL );
    if( FAILED(ret) ) {
    //    DEBUG( "�v���C�}���T�E���h�o�b�t�@�쐬���s\n","" );
        return 0;
    }
    
    //�o�b�t�@ �I�u�W�F�N�g�̔\�͂��擾����B
    DSCAPS caps;
    pDS8->GetCaps(&caps);
	
    // �v���C�}���o�b�t�@�̃X�e�[�^�X������
    wf.cbSize = sizeof( WAVEFORMATEX );
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 2;
    wf.nSamplesPerSec = 44100;
    wf.wBitsPerSample = 16;
    wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
    wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
    ret = lpPrimary->SetFormat( &wf );
    if( FAILED(ret) ) {
     //   DEBUG( "�v���C�}���o�b�t�@�̃X�e�[�^�X���s\n","" );
        return 0;
    }
	
	return 1;
}

void vnDirectSound::terminate(void)
{
	SAFE_RELEASE(lpPrimary);
	SAFE_RELEASE(pDS8);
}
