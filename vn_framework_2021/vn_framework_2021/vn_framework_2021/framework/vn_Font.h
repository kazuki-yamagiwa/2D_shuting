//--------------------------------------------------------------//
//	"vn_Font.h"													//
//		�t�H���g�`��											//
//													2021/04/01	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once

#define vnFontSTRING_MAX	(0x0400)	//1�t���[���Ŏ��s�ł���render�̐�
#define vnFontCHARACTER_MAX	(0x2000)	//1�t���[���ŕ`��ł��镶���̐�

#define vnFontNUM_MAX		(256)	//�m�ۂ��Ă�����g�p�\�t�H���g���̍ő吔

class vnFont
{
private:
	static WCHAR	fontName[vnFontNUM_MAX][64];
	static int		fontNum;

	static ID2D1SolidColorBrush	*pBrush;
	static IDWriteTextFormat	*pTextFormat;
	static D2D1_RECT_F			rect;

	static float	Size;
	static float	X;
	static float	Y;
	static DWORD	Color;
	
	struct stStringInfo
	{
		float x;
		float y;
		DWORD color;
		WCHAR *ptr;
		UINT32 count;
		IDWriteTextFormat* textFormat;
	};
	static stStringInfo	strInfo[vnFontSTRING_MAX];
	static int			registerNum;
	static int			registerCount;
	static WCHAR		*allocPtr;
	static WCHAR		*currentPtr;

	static IDWriteTextFormat	*currentTextFormat;
	
	static void registerString(const WCHAR *string, UINT32 count);
	
public:
	//[�V�X�e���Ǘ��֐�
	static bool initialize();
	static void terminate();
	static void renderString();
	//]

	//�g�p�ł���t�H���g���̎擾
	static int getFontNum(void);

	//�g�p�ł���t�H���g���̎擾
	static WCHAR *getFontName(int id);
	
	//�t�H���g�̍쐬
	static IDWriteTextFormat *create(const WCHAR *fontname, int size);
	
	//�e��ݒ�
	static void setPos(float x, float y);
	static void setPosX(float x);
	static void setPosY(float y);
	static void setColor(DWORD color);
	static void setTextFormat(IDWriteTextFormat* tf = NULL);
	
	//�e��擾
	static float getPosX();
	static float getPosY();
	static DWORD getColor();

	//������̕`��(���C�h����)
	static void print(float x, float y, DWORD color, const WCHAR *string, ...);
	static void print(float x, float y, const WCHAR *string, ...);
	static void print(const WCHAR *string, ...);

	//������̕`��(���C�h����/�������w��t��)
	static void printCount(float x, float y, DWORD color, int count, const WCHAR *string, ...);
	static void printCount(float x, float y, int count, const WCHAR *string, ...);
	static void printCount(int count, const WCHAR *string, ...);

	//�W���o�͂ւ̕�����`��(���C�h����)
	static void output(const WCHAR *string, ...);

};