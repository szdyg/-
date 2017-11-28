#pragma once

#include"stdafx.h"
#include "resource.h"
#include "微信打飞机.h"

/*飞机UI资源*/
enum PALNEUI
{
	BACKGROUND = 0,
	BIGPALNE,
	EXITBTN,
	GAMELOGO,
	MIDDLEPALNE,
	PLAYBTN,
	RESTARTBTN,
	SCORE,
	SMALLPLANE,
	STARTBTN
};


/*飞机类型*/
enum PLANETYPE
{
	SMALL,		//大
	MIDDLE,		//中
	BIG			//小
};


/*飞机类*/
class CPlane
{
public:
	CPlane();
	~CPlane();
	BOOL BeHit(POINT pos);	//被点击
	VOID Draw(HDC hdcMem, HDC hdcTemp);	//飞机绘制
	BOOL IsCrashed();		//判断飞机是否被摧毁
	BOOL Move();			//移动飞机坐标
	DWORD Getpoint();		//返回飞机分数


protected:
	WORD		Speed;	//飞机速度
	BOOL		crash;	//飞机是否被摧毁
	HINSTANCE   hIns;	//实例句柄
	PLANETYPE	type;	//飞机类型
	DWORD		dwHP;	//飞机血量
	DWORD		dwHit;	//飞机被击中次数
	POINT		pos;	//飞机位置
	SIZE		size;	//飞机大小
	HBITMAP		hBmp;	//飞机UI图片
};
