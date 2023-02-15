//--------------------------------------------------------------//
//	"vn_sound.cpp"												//
//		WAVE�t�@�C���Đ��N���X									//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#include "../framework.h"
#include "vn_environment.h"

vnSound::vnSound(const WCHAR *path)
{
	HRESULT hr;
    MMCKINFO mSrcWaveFile;
    MMCKINFO mSrcWaveFmt;
    MMCKINFO mSrcWaveData;
    LPWAVEFORMATEX wf;

	pDSBuffer = NULL;

	// WAV�t�@�C�������[�h
    HMMIO hSrc;
    hSrc = mmioOpen( (LPWSTR)path, NULL,MMIO_ALLOCBUF|MMIO_READ|MMIO_COMPAT );
    if( !hSrc ) {
    //    DEBUG( "WAV�t�@�C�����[�h�G���[\n","" );
        return;
    }

    // 'WAVE'�`�����N�`�F�b�N
    ZeroMemory( &mSrcWaveFile,sizeof(mSrcWaveFile) );
	hr = mmioDescend( hSrc,&mSrcWaveFile,NULL,MMIO_FINDRIFF );
    if( mSrcWaveFile.fccType!=mmioFOURCC('W','A','V','E') ) {
    //    DEBUG( "WAVE�`�����N�`�F�b�N�G���[\n","" );
        mmioClose( hSrc,0 );
        return;
    }

    // 'fmt '�`�����N�`�F�b�N
    ZeroMemory( &mSrcWaveFmt,sizeof(mSrcWaveFmt) );
	hr = mmioDescend( hSrc,&mSrcWaveFmt,&mSrcWaveFile,MMIO_FINDCHUNK );
    if( mSrcWaveFmt.ckid!=mmioFOURCC('f','m','t',' ') ) {
    //    DEBUG( "fmt �`�����N�`�F�b�N�G���[\n","" );
        mmioClose( hSrc,0 );
        return;
    }

    // �w�b�_�T�C�Y�̌v�Z
    int iSrcHeaderSize = mSrcWaveFmt.cksize;
    if( iSrcHeaderSize<sizeof(WAVEFORMATEX) )
        iSrcHeaderSize=sizeof(WAVEFORMATEX);

    // �w�b�_�������m��
    wf = (LPWAVEFORMATEX)malloc( iSrcHeaderSize );
    if( !wf ) {
    //    DEBUG( "�������m�ۃG���[\n","" );
        mmioClose( hSrc,0 );
        return;
    }
    ZeroMemory( wf,iSrcHeaderSize );

    // WAVE�t�H�[�}�b�g�̃��[�h
	hr = mmioRead( hSrc,(char*)wf,mSrcWaveFmt.cksize );
    if( FAILED(hr) ) {
     //   DEBUG( "WAVE�t�H�[�}�b�g���[�h�G���[\n","" );
        free( wf );
        mmioClose( hSrc,0 );
        return;
    }
 //   DEBUG( "�`�����l����       = %d\n",wf->nChannels );
 //   DEBUG( "�T���v�����O���[�g = %d\n",wf->nSamplesPerSec );
 //   DEBUG( "�r�b�g���[�g       = %d\n",wf->wBitsPerSample );


    // fmt�`�����N�ɖ߂�
    mmioAscend( hSrc,&mSrcWaveFmt,0 );

    // data�`�����N��T��
    while(1) {
        // ����
		hr = mmioDescend( hSrc,&mSrcWaveData,&mSrcWaveFile,0 );
        if( FAILED(hr) ) {
         //   DEBUG( "data�`�����N��������Ȃ�\n","" );
            free( wf );
            mmioClose( hSrc,0 );
            return;
        }
        if( mSrcWaveData.ckid==mmioStringToFOURCC(L"data",0) )
            break;
        // ���̃`�����N��
		hr = mmioAscend( hSrc,&mSrcWaveData,0 );
    }
 //   DEBUG( "�f�[�^�T�C�Y       = %d\n",mSrcWaveData.cksize );


    // �T�E���h�o�b�t�@�̍쐬
    DSBUFFERDESC dsdesc;
    ZeroMemory( &dsdesc,sizeof(DSBUFFERDESC) );
    dsdesc.dwSize = sizeof( DSBUFFERDESC );
	dsdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER;
    dsdesc.dwBufferBytes = mSrcWaveData.cksize;
    dsdesc.lpwfxFormat = wf;
    dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	hr = vnDirectSound::getDevice()->CreateSoundBuffer( &dsdesc,&pDSBuffer,NULL );
    if( FAILED(hr) )
	{
     //   DEBUG( "�T�E���h�o�b�t�@�̍쐬�G���[\n","" );
        free( wf );
        mmioClose( hSrc,0 );
        return;
    }

    // ���b�N�J�n
    LPVOID pMem1,pMem2;
    DWORD dwSize1,dwSize2;
	hr = pDSBuffer->Lock( 0,mSrcWaveData.cksize,&pMem1,&dwSize1,&pMem2,&dwSize2,0 );
    if( FAILED(hr) )
	{
    //    DEBUG( "���b�N���s\n","" );
        free( wf );
        mmioClose( hSrc,0 );
        return;
    }

    // �f�[�^��������
    mmioRead( hSrc,(char*)pMem1,dwSize1 );
    mmioRead( hSrc,(char*)pMem2,dwSize2 );

    // ���b�N����
    pDSBuffer->Unlock( pMem1,dwSize1,pMem2,dwSize2 );

    // �w�b�_�p���������J��
    free( wf );

    // WAV�����
    mmioClose( hSrc,0 );

	pDSBuffer->SetCurrentPosition(0);
}

vnSound::~vnSound()
{
	SAFE_RELEASE(pDSBuffer);
}

bool vnSound::play(bool loop)
{
	if(pDSBuffer)
	{
		HRESULT hr = pDSBuffer->Play(0, 0, loop==true?DSBPLAY_LOOPING:0);
		return hr==DS_OK ;
	}
	return false;
}

bool vnSound::stop()
{
	if(pDSBuffer)
	{
		HRESULT hr = pDSBuffer->Stop();
		return hr==DS_OK ;
	}
	return false;
}

bool vnSound::isPlaying(void)
{
	if(pDSBuffer)
	{
		DWORD stat;
		pDSBuffer->GetStatus(&stat);
		return (stat&DSBSTATUS_PLAYING)!=0;
	}
	return false;
}

bool vnSound::isStopped()
{
	return !isPlaying();
}

bool vnSound::setVolume(LONG lVolume)
{
	if(pDSBuffer)
	{
		if(lVolume>DSBVOLUME_MAX || lVolume<DSBVOLUME_MIN)return false;
		HRESULT hr = pDSBuffer->SetVolume(lVolume);
		return hr==DS_OK;
	}
	return false;
}

bool vnSound::setPan(LONG lPan)
{
	if(pDSBuffer)
	{
		if(lPan<DSBPAN_LEFT || lPan>DSBPAN_RIGHT)return false;
		HRESULT hr = pDSBuffer->SetPan(lPan);
		switch(hr)
		{
		case DS_OK:break;
		case DSERR_CONTROLUNAVAIL:	OutputDebugString(L"onSound::volume::set DSERR_CONTROLUNAVAIL\n");break;
		case DSERR_GENERIC:			OutputDebugString(L"onSound::volume::set DSERR_GENERIC\n");break;
		case DSERR_INVALIDPARAM:	OutputDebugString(L"onSound::volume::set DSERR_INVALIDPARAM\n");break;
		case DSERR_PRIOLEVELNEEDED:	OutputDebugString(L"onSound::volume::set DSERR_PRIOLEVELNEEDED\n");break;
		default:					OutputDebugString(L"onSound::volume::set Unknown\n");break;
		}
		return hr==DS_OK;
	}
	return false;
}

bool vnSound::setFrequency(DWORD dwFrequency)
{
	if(pDSBuffer)
	{
		HRESULT hr = pDSBuffer->SetFrequency(dwFrequency);
		return hr==DS_OK;
	}
	return false;
}

LONG vnSound::getVolume()
{
	if(pDSBuffer)
	{
		LONG ret=0;
		HRESULT hr = pDSBuffer->GetVolume(&ret);
		return ret;
	}
	return 0;
}

LONG vnSound::getPan()
{
	if(pDSBuffer)
	{
		LONG ret=0;
		HRESULT hr = pDSBuffer->GetPan(&ret);
		switch(hr)
		{
		case DS_OK:break;
		case DSERR_CONTROLUNAVAIL:	OutputDebugString(L"onSound::volume::set DSERR_CONTROLUNAVAIL\n");break;
		case DSERR_GENERIC:			OutputDebugString(L"onSound::volume::set DSERR_GENERIC\n");break;
		case DSERR_INVALIDPARAM:	OutputDebugString(L"onSound::volume::set DSERR_INVALIDPARAM\n");break;
		case DSERR_PRIOLEVELNEEDED:	OutputDebugString(L"onSound::volume::set DSERR_PRIOLEVELNEEDED\n");break;
		default:					OutputDebugString(L"onSound::volume::set Unknown\n");break;
		}
		return ret;
	}
	return 0;
}

DWORD vnSound::getFrequency()
{
	if(pDSBuffer)
	{
		DWORD ret=0;
		HRESULT hr = pDSBuffer->GetFrequency(&ret);
		return ret;
	}
	return 0;
}

