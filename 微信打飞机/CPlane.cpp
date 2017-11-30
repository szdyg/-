#pragma once

#include "stdafx.h"
#include "CPlane.h"

UINT CPlane::uBigNumHave = 0;
UINT CPlane::uBigNum = 2;

//************************************
// 函数名称:    RandPlane
// 函数全称:    RandPlane
// 返回类型:    PLANETYPE
// 权限:   	   public 
// Qualifier: 
// 说明:		随机产生飞机类型
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
// 函数名称:    CPlane
// 函数全称:    CPlane::CPlane
// 返回类型:    
// 权限:   	   public 
// Qualifier: 
// 说明:	 飞机类初始化函数
//************************************
CPlane::CPlane()
{

	this->hIns = GetModuleHandle(NULL);
	this->dwHit = 0;
	this->crash = FALSE;
	this->crashshowed = FALSE;
	//初始化类型
	this->type = RandPlane();
	//根据飞机类型初始化资源
	switch (this->type)
	{
	case SMALL:
	{
		this->Speed = 3;
		this->hBmp = LoadBitmap(this->hIns, MAKEINTRESOURCE(IDB_SMALLPLANE));
		BITMAP	bmp;
		GetObject(this->hBmp, sizeof(bmp), &bmp);
		this->size.cx = bmp.bmWidth;
		this->size.cy = bmp.bmHeight / 2;	//2层图片
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
		this->size.cy = bmp.bmHeight / 3;	//3层图片
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
		this->size.cy = bmp.bmHeight / 4;	//4层图片
		this->dwHP = 3;
	}
	break;
	default:
		break;
	}

	//随机初始位置
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
// 函数名称:    BeHit
// 函数全称:    CPlane::BeHit
// 返回类型:    BOOL
// 权限:   	   public 
// Qualifier: 
// 参数: 	   POINT pos
// 说明:			判断自身是否被击中，同时判断自身是否还有血
//************************************
BOOL CPlane::BeHit(POINT pos)
{
	RECT	rt;

	rt.left = this->pos.x;
	rt.top = this->pos.y;
	rt.right = rt.left + this->size.cx;
	rt.bottom = rt.top + this->size.cy;

	//判断是否被击中
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
	//大飞机数量
	if (this->type == BIG)
	{
		CPlane::BigNumHaveSub();
	}

}

//************************************
// 函数名称:    Draw
// 函数全称:    CPlane::Draw
// 返回类型:    VOID
// 权限:   	   public 
// Qualifier: 
// 参数: 	   HDC hdcMem		接受VOID DrawWindow的hdcMem
// 参数: 	   HDC hdcTemp		接受VOID DrawWindow的hdcTemp
// 说明:		绘制飞机位置
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
// 函数名称:    IsCrashed
// 函数全称:    CPlane::IsCrashed
// 返回类型:    BOOL
// 权限:   	   public 
// Qualifier: 
// 说明:			返回飞机摧毁状态
//************************************
BOOL CPlane::IsCrashed()
{
	return this->crash;
}

//************************************
// 函数名称:    Move
// 函数全称:    CPlane::Move
// 返回类型:    BOOL
// 权限:   	   public 
// Qualifier: 
// 说明:			移动飞机，并判断是否到达终点
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
// 函数名称:    Getpoint
// 函数全称:    CPlane::Getpoint
// 返回类型:    DWORD
// 权限:   	   public 
// Qualifier: 
// 说明:			飞机摧毁后返回分数信息HP就是分数
//************************************
DWORD CPlane::Getpoint()
{
	return this->dwHP;
}

BOOL CPlane::IsCrashShowed()
{
	return this->crashshowed;
}

