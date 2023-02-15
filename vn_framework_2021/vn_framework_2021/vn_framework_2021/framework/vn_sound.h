//--------------------------------------------------------------//
//	"vn_sound.h"												//
//		WAVE�t�@�C���Đ��N���X									//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once

class vnSound
{
private:
	IDirectSoundBuffer *pDSBuffer;
	
public:
	//�R���X�g���N�^
	vnSound(const WCHAR *path);
	//�f�X�g���N�^
	~vnSound();
	
	bool play(bool loop=false);	//�Đ�
	bool stop();				//��~
	
	bool isPlaying();	//�Đ��������ׂ�
	bool isStopped();	//��~�������ׂ�
	
	//�e��ݒ�
	bool setVolume(LONG lVolume);			//���� : DSBVOLUME_MAX (�����Ȃ�:0) ���� DSBVOLUME_MIN (����:-10,000)
	bool setPan(LONG lPan);					//���E�̃`�����l���̑��΃{�����[�� : DSBPAN_LEFT(-10,000) ���� DSBPAN_RIGHT(10,000)
	bool setFrequency(DWORD dwFrequency);	//�I�[�f�B�I �o�b�t�@���Đ�����Ă�����g��(Hz �P��) / �f�t�H���g�l : DSBFREQUENCY_ORIGINAL
	
	//�e��擾
	LONG getVolume();
	LONG getPan();
	DWORD getFrequency();

};

