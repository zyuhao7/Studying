//=============================================================================
// Name: SkyBoxClass.h
//	Des: һ����װ����ά��պ�ϵͳ�����ͷ�ļ�
// 2013�� 3��24��  Create by ǳī 
//=============================================================================
#pragma once
#include "D3DUtil.h"

//Ϊ��պ��ඨ��һ��FVF�����ʽ
struct SKYBOXVERTEX
{
	float	x,y,z;
	float	u,v;
};
#define D3DFVF_SKYBOX D3DFVF_XYZ|D3DFVF_TEX1


class SkyBoxClass
{
private:
	LPDIRECT3DDEVICE9				m_pd3dDevice;			//D3D�豸����
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;		//���㻺�����
	LPDIRECT3DTEXTURE9			m_pTexture[5];			//5������ӿڶ���
	float										m_Length;					//��պб߳�

public:
	SkyBoxClass( LPDIRECT3DDEVICE9  pDevice );		//���캯��
	virtual ~SkyBoxClass(void);								//��������

public:
	BOOL	InitSkyBox( float Length );   //��ʼ����պк���
	BOOL	LoadSkyTextureFromFile(const wchar_t *pFrontTextureFile, const  wchar_t *pBackTextureFile, const wchar_t *pLeftTextureFile, const wchar_t *pRightTextureFile, const wchar_t *pTopTextureFile);  //���ļ�������պ���������ϵ�����
	VOID		RenderSkyBox( D3DXMATRIX *pMatWorld, BOOL bRenderFrame ); //��Ⱦ��պ�,���ݵ�һ�������趨��պ�������󣬵ڶ�������ѡ���Ƿ���Ⱦ���߿�

};

