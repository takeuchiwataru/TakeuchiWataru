//=============================================================================
//
// シーン3D処理 [scene3D.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

//*********************************************************************
//シーン3Dクラスの定義
//*********************************************************************
class CShadow : public  CScene3D//派生クラス
{
public:
	typedef enum
	{
		SHADOWTYPE_NORMAL = 0,
		SHADOWTYPE_BILL,
		SHADOWTYPE_MAX,
	}SHADOWTYPE;
	CShadow();
	~CShadow();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CShadow *Create(D3DXVECTOR3 pos, float fWidth, float fDepth, D3DXCOLOR col,SHADOWTYPE type);
	static HRESULT Load(void);
	static void UnLoad(void);

	//メンバ変数
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff = NULL;	//頂点バッファへのポインタ
	static LPDIRECT3DTEXTURE9			m_pTexture[SHADOWTYPE_MAX];	//テクスチャへのポインタ
	float								m_Height;

	D3DXVECTOR3							m_pos;							//位置
	D3DXVECTOR3							m_rot;							//向き
	D3DXCOLOR							m_col;
	D3DXMATRIX							m_mtxWorld;						//ワールドマトリックス
	float								m_fWidth, m_fDepth;				//幅　奥行き

	CScene3D							*m_pScene3D;
	SHADOWTYPE							m_Type;
};

#endif
