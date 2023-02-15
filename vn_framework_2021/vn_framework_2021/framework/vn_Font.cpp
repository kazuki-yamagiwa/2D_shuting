//--------------------------------------------------------------//
//	"vn_Font.cpp"												//
//		フォント描画											//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#include "../framework.h"
#include "vn_environment.h"

ID2D1SolidColorBrush	*vnFont::pBrush = NULL;
IDWriteTextFormat		*vnFont::pTextFormat = NULL;
D2D1_RECT_F				vnFont::rect;

float		vnFont::Size = 16.0f;
float		vnFont::X = 0.0f;
float		vnFont::Y = 0.0f;
DWORD		vnFont::Color = 0xffffffff;

vnFont::stStringInfo	vnFont::strInfo[vnFontSTRING_MAX];
int			vnFont::registerNum=0;
int			vnFont::registerCount = 0;
WCHAR		*vnFont::allocPtr=NULL;
WCHAR		*vnFont::currentPtr=NULL;

bool vnFont::initialize()
{
	registerNum = 0;
	registerCount = 0;
	allocPtr = new WCHAR[vnFontCHARACTER_MAX];
	currentPtr = allocPtr;

	HRESULT hr;
	
	//ブラシの生成
	hr = vnDirect2D::getRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
	if (hr != S_OK)
	{
		return false;
	}

	//フォントの作成
	if(create(L"Meiryo"/*L"ＭＳ ゴシック"*/, (int)Size)==false)
	{
		return false;
	}

	rect.left = 0.0f;
	rect.top = 0.0f;
	rect.right = (float)CLIENT_WIDTH;
	rect.bottom = (float)CLIENT_HEIGHT;
	
	return true;
}

void vnFont::terminate()
{
	delete[] allocPtr;
	SAFE_RELEASE(pTextFormat);
	SAFE_RELEASE(pBrush);
}

void vnFont::registerString(const WCHAR *string, UINT32 count)
{
#pragma warning(push)
#pragma warning(disable:4311)
#pragma warning(disable:4302)
	if(string==NULL)return;
	if(registerNum>=vnFontSTRING_MAX)return;
	if (registerCount+count >= vnFontCHARACTER_MAX)return;
	strInfo[registerNum].x = X;
	strInfo[registerNum].y = Y;
	strInfo[registerNum].color = Color;
	strInfo[registerNum].ptr = currentPtr;
	strInfo[registerNum].count = count;
	wcsncpy_s((WCHAR*)currentPtr, vnFontCHARACTER_MAX-(reinterpret_cast<int>(currentPtr)- reinterpret_cast<int>(allocPtr)), string, count);
	currentPtr+=count;
	registerNum++;
	registerCount += count;
#pragma warning(pop)
}

void vnFont::renderString()
{
	if(pTextFormat==NULL)return;

	static float reciprocal = 1.0f / 255.0f;
	for(int i=0; i<registerNum; i++)
	{
		//描画位置の設定
		rect.left = strInfo[i].x;
		rect.top = strInfo[i].y;

		//描画色の設定
		if (!i || Color != strInfo[i].color)
		{
			Color = strInfo[i].color;

			D2D1_COLOR_F col;
			col.r = (float)((Color & 0x00ff0000) >> 16) * reciprocal;
			col.g = (float)((Color & 0x0000ff00) >>  8) * reciprocal;
			col.b = (float)((Color & 0x000000ff) >>  0) * reciprocal;
			col.a = (float)((Color & 0xff000000) >> 24) * reciprocal;
			pBrush->SetColor(&col);
		}

		//テキストの描画
		vnDirect2D::getRenderTarget()->DrawText(
			strInfo[i].ptr,
			strInfo[i].count,
			pTextFormat,
			&rect,
			pBrush,
			D2D1_DRAW_TEXT_OPTIONS_NONE
			);
	}
	registerNum = 0;
	registerCount = 0;
	currentPtr = allocPtr;
	return;
}

bool vnFont::create(const WCHAR *fontname, int size)
{
	HRESULT hr;

	SAFE_RELEASE(pTextFormat);

	//テキストフォーマットの生成
	hr = vnDirect2D::getDWFactory()->CreateTextFormat(
		fontname,
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		Size,
		L"",
		&pTextFormat
		);
	if (hr != S_OK)
	{
		return false;
	}

	return true;
}

void vnFont::setPos(float x, float y)
{
	X = x;
	Y = y;
}

void vnFont::setPosX(float x)
{
	X = x;
}

void vnFont::setPosY(float y)
{
	Y = y;
}

void vnFont::setColor(DWORD color)
{
	Color = color;
}

float vnFont::getPosX()
{
	return X;
}

float vnFont::getPosY()
{
	return Y;
}

DWORD vnFont::getColor()
{
	return Color;
}

//文字列の描画(ワイド文字)
void vnFont::print(float x, float y, DWORD color, const WCHAR *string, ...)
{
	if (string == NULL)return;

	X = x;
	Y = y;
	Color = color;

	va_list	va;
	va_start(va, string);
	WCHAR buf[0x100];
	vswprintf_s(buf, string, va);
	va_end(va);

	registerString(buf, (UINT32)wcslen(buf));
}

void vnFont::print(float x, float y, const WCHAR *string, ...)
{
	if (string == NULL)return;

	X = x;
	Y = y;

	va_list	va;
	va_start(va, string);
	WCHAR buf[0x100];
	vswprintf_s(buf, string, va);
	va_end(va);

	registerString(buf, (UINT32)wcslen(buf));
}

void vnFont::print(const WCHAR *string, ...)
{
	if (string == NULL)return;

	va_list	va;
	va_start(va, string);
	WCHAR buf[0x100];
	vswprintf_s(buf, string, va);
	va_end(va);

	registerString(buf, (UINT32)wcslen(buf));
}

//文字列の描画(ワイド文字/文字数指定付き)
void vnFont::printCount(float x, float y, DWORD color, int count, const WCHAR *string, ...)
{
	if (string == NULL)return;

	X = x;
	Y = y;
	Color = color;

	va_list	va;
	va_start(va, string);
	WCHAR buf[0x100];
	vswprintf_s(buf, string, va);
	va_end(va);

	registerString(buf, (UINT32)count);
}

void vnFont::printCount(float x, float y, int count, const WCHAR *string, ...)
{
	if (string == NULL)return;

	X = x;
	Y = y;

	va_list	va;
	va_start(va, string);
	WCHAR buf[0x100];
	vswprintf_s(buf, string, va);
	va_end(va);

	registerString(buf, (UINT32)count);
}

void vnFont::printCount(int count, const WCHAR *string, ...)
{
	if (string == NULL)return;

	va_list	va;
	va_start(va, string);
	WCHAR buf[0x100];
	vswprintf_s(buf, string, va);
	va_end(va);

	registerString(buf, (UINT32)count);
}

//標準出力への文字列描画(ワイド文字)(ワイド文字)
void vnFont::output(const WCHAR *string, ...)
{
	if (string == NULL)return;

	va_list	va;
	va_start(va, string);
	WCHAR buf[0x100];
	vswprintf_s(buf, string, va);
	va_end(va);

	OutputDebugStringW(buf);
}
