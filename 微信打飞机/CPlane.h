#pragma once

#include"stdafx.h"
#include "resource.h"
#include "΢�Ŵ�ɻ�.h"

/*�ɻ�UI��Դ*/
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


/*�ɻ�����*/
enum PLANETYPE
{
	SMALL,		//��
	MIDDLE,		//��
	BIG			//С
};


/*�ɻ���*/
class CPlane
{
public:
	CPlane();
	~CPlane();
	BOOL BeHit(POINT pos);	//�����
	VOID Draw(HDC hdcMem, HDC hdcTemp);	//�ɻ�����
	BOOL IsCrashed();		//�жϷɻ��Ƿ񱻴ݻ�
	BOOL Move();			//�ƶ��ɻ�����
	DWORD Getpoint();		//���طɻ�����


protected:
	WORD		Speed;	//�ɻ��ٶ�
	BOOL		crash;	//�ɻ��Ƿ񱻴ݻ�
	HINSTANCE   hIns;	//ʵ�����
	PLANETYPE	type;	//�ɻ�����
	DWORD		dwHP;	//�ɻ�Ѫ��
	DWORD		dwHit;	//�ɻ������д���
	POINT		pos;	//�ɻ�λ��
	SIZE		size;	//�ɻ���С
	HBITMAP		hBmp;	//�ɻ�UIͼƬ
};
