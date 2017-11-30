#pragma once

#include "stdafx.h"
#include "CPlane.h"

UINT CPlane::uBigNumHave = 0;
UINT CPlane::uBigNum = 2;

//************************************
// ��������:    RandPlane
// ����ȫ��:    RandPlane
// ��������:    PLANETYPE
// Ȩ��:   	   public 
// Qualifier: 
// ˵��:		��������ɻ�����
//************************************
PLANETYPE	RandPlane()
{
	int temp;
	srand(GetTickCount());
	temp = rand() % 3;

	switch (temp)
	{
	case 0:
		return SMALL;
		break;

	case 1:
		return MIDDLE;
		break;

	default:
		if (CPlane::uBigNumHave > CPlane::uBigNum)
		{
			temp = rand() % 2;
			if (temp == 0)
			{
				return SMALL;
			}
			return	MIDDLE;
		}
		return BIG;
		break;
	}
}



//************************************
// ��������:    CPlane
// ����ȫ��:    CPlane::CPlane
// ��������:    
// Ȩ��:   	   public 
// Qualifier: 
// ˵��:	 �ɻ����ʼ������
//************************************
CPlane::CPlane()
{

	this->hIns = GetModuleHandle(NULL);
	this->dwHit = 0;
	this->crash = FALSE;
	this->crashshowed = FALSE;
	//��ʼ������
	this->type = RandPlane();
	//���ݷɻ����ͳ�ʼ����Դ
	switch (this->type)
	{
	case SMALL:
	{
		this->Speed = 3;
		this->hBmp = LoadBitmap(this->hIns, MAKEINTRESOURCE(IDB_SMALLPLANE));
		BITMAP	bmp;
		GetObject(this->hBmp, sizeof(bmp), &bmp);
		this->size.cx = bmp.bmWidth;
		this->size.cy = bmp.bmHeight / 2;	//2��ͼƬ
		this->dwHP = 1;
	}
	break;

	case MIDDLE:
	{
		this->Speed = 2;
		this->hBmp = LoadBitmap(this->hIns, MAKEINTRESOURCE(IDB_MIDDLEPALNE));
		BITMAP	bmp;
		GetObject(hBmp, sizeof(BITMAP), &bmp);
		this->size.cx = bmp.bmWidth;
		this->size.cy = bmp.bmHeight / 3;	//3��ͼƬ
		this->dwHP = 2;
	}
	break;

	case BIG:
	{
		CPlane::BigNumHaveAdd();
		this->Speed = 1;
		this->hBmp = LoadBitmap(this->hIns, MAKEINTRESOURCE(IDB_BIGPALNE));
		BITMAP	bmp;
		GetObject(this->hBmp, sizeof(BITMAP), &bmp);
		this->size.cx = bmp.bmWidth;
		this->size.cy = bmp.bmHeight / 4;	//4��ͼƬ
		this->dwHP = 3;
	}
	break;
	default:
		break;
	}

	//�����ʼλ��
	srand(GetTickCount());
	this->pos.y = 0 - this->size.cy - (rand() % 20);
	this->pos.x = rand() % (GAMEWNDWIDTH - this->size.cy);
}

VOID CPlane::BigNumHaveAdd()
{
	CPlane::uBigNumHave -= 1;
}

VOID CPlane::BigNumHaveSub()
{
	CPlane::uBigNumHave += 1;
}

//************************************
// ��������:    BeHit
// ����ȫ��:    CPlane::BeHit
// ��������:    BOOL
// Ȩ��:   	   public 
// Qualifier: 
// ����: 	   POINT pos
// ˵��:			�ж������Ƿ񱻻��У�ͬʱ�ж������Ƿ���Ѫ
//************************************
BOOL CPlane::BeHit(POINT pos)
{
	RECT	rt;

	rt.left = this->pos.x;
	rt.top = this->pos.y;
	rt.right = rt.left + this->size.cx;
	rt.bottom = rt.top + this->size.cy;

	//�ж��Ƿ񱻻���
	if (PtInRect(&rt, pos))
	{
		this->dwHit++;
		PlaySound(MAKEINTRESOURCE(IDR_CRASHWAV), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
		if (dwHit == dwHP)
		{
			this->crash = TRUE;
		}
		return	TRUE;
	}
	return FALSE;
}


CPlane::~CPlane()
{
	//��ɻ�����
	if (this->type == BIG)
	{
		CPlane::BigNumHaveSub();
	}

}

//************************************
// ��������:    Draw
// ����ȫ��:    CPlane::Draw
// ��������:    VOID
// Ȩ��:   	   public 
// Qualifier: 
// ����: 	   HDC hdcMem		����VOID DrawWindow��hdcMem
// ����: 	   HDC hdcTemp		����VOID DrawWindow��hdcTemp
// ˵��:		���Ʒɻ�λ��
//************************************
VOID CPlane::Draw(HDC hdcMem, HDC hdcTemp)
{

	SelectObject(hdcTemp, this->hBmp);
	TransparentBlt(hdcMem, this->pos.x, this->pos.y, this->size.cx, this->size.cy,
		hdcTemp, 0, (this->dwHit*this->size.cy), this->size.cx, this->size.cy,
		RGB(255, 255, 255));

	if (this->IsCrashed())
	{
		this->crashshowed = TRUE;
	}
	
}

//************************************
// ��������:    IsCrashed
// ����ȫ��:    CPlane::IsCrashed
// ��������:    BOOL
// Ȩ��:   	   public 
// Qualifier: 
// ˵��:			���طɻ��ݻ�״̬
//************************************
BOOL CPlane::IsCrashed()
{
	return this->crash;
}

//************************************
// ��������:    Move
// ����ȫ��:    CPlane::Move
// ��������:    BOOL
// Ȩ��:   	   public 
// Qualifier: 
// ˵��:			�ƶ��ɻ������ж��Ƿ񵽴��յ�
//************************************
BOOL CPlane::Move()
{
	
	this->pos.y += this->Speed;
	if (this->pos.y + this->size.cy >= GAMEWNDHEIGHT)
	{
		return TRUE;
	}
	return FALSE;
}

//************************************
// ��������:    Getpoint
// ����ȫ��:    CPlane::Getpoint
// ��������:    DWORD
// Ȩ��:   	   public 
// Qualifier: 
// ˵��:			�ɻ��ݻٺ󷵻ط�����ϢHP���Ƿ���
//************************************
DWORD CPlane::Getpoint()
{
	return this->dwHP;
}

BOOL CPlane::IsCrashShowed()
{
	return this->crashshowed;
}

