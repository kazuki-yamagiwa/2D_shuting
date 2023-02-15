//--------------------------------------------------------------//
//	"vn_Font.h"													//
//		フォント描画											//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once

#define vnFontSTRING_MAX	(0x0400)	//1フレームで実行できるrenderの数
#define vnFontCHARACTER_MAX	(0x2000)	//1フレームで描画できる文字の数

class vnFont
{
private:
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
	};
	static stStringInfo	strInfo[vnFontSTRING_MAX];
	static int			registerNum;
	static int			registerCount;
	static WCHAR		*allocPtr;
	static WCHAR		*currentPtr;
	
	static void registerString(const WCHAR *string, UINT32 count);
	
public:
	//[システム管理関数
	static bool initialize();
	static void terminate();
	static void renderString();
	//]
	
	//フォントの作成
	static bool create(const WCHAR *fontname, int size);
	
	//各種設定
	static void setPos(float x, float y);
	static void setPosX(float x);
	static void setPosY(float y);
	static void setColor(DWORD color);
	
	//各種取得
	static float getPosX();
	static float getPosY();
	static DWORD getColor();

	//文字列の描画(ワイド文字)
	static void print(float x, float y, DWORD color, const WCHAR *string, ...);
	static void print(float x, float y, const WCHAR *string, ...);
	static void print(const WCHAR *string, ...);

	//文字列の描画(ワイド文字/文字数指定付き)
	static void printCount(float x, float y, DWORD color, int count, const WCHAR *string, ...);
	static void printCount(float x, float y, int count, const WCHAR *string, ...);
	static void printCount(int count, const WCHAR *string, ...);

	//標準出力への文字列描画(ワイド文字)
	static void output(const WCHAR *string, ...);

};
