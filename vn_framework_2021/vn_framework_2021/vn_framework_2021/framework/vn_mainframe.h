//--------------------------------------------------------------//
//	"vn_mainframe.h"											//
//		���C���t���[��											//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once

class vnMainFrame
{
public:

	static float clearColor[4];		//��ʂ̃N���A�J���[(RGBA:0.0�`1.0)

	//������
	static bool initialize(void *hWnd, void *hInst);

	//�I��
	static void terminate();

	//���s
	static void execute();
};
