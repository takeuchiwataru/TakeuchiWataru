//=============================================================================
//
// エフェクト処理 [effect.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "billboard.h"

//*********************************************************************
//ビルボードクラスの定義
//*********************************************************************
class CEffect : public CSceneBillBoard //派生クラス
{
public:
	typedef enum
	{
		EFFECTTEX_NORMAL000 = 0,	//通常
		EFFECTTEX_BUBBLE000,		//泡
		EFFECTTEX_HAHEN000,			//破片
		EFFECTTEX_HAHEN001,			//破片2
		EFFECTTEX_SMOKE,			//砂煙
		EFFECTTEX_MAX				//テクスチャの総数
	}EFFECTTEX;

	CEffect();
	~CEffect();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,
							float fWidth, float fHeight,int nNumMax,int nLife, EFFECTTEX TexType);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[EFFECTTEX_MAX];	// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_move;						// 移動量
	D3DXVECTOR3					m_posold;					// 前回の位置
	float						m_fWidth, m_fHeight;		// 幅 高さ
	D3DXMATRIX					m_mtrxWorld;				// ワールドマトリックス
	D3DXCOLOR					m_Col;						// カラー
	int							m_nNumMax;					// エフェクトのポリゴン数
	int							m_nLife;					// エフェクトが消えるまでの時間
	float						m_fAlpha;					// エフェクトの透明度
	int							m_nCntTimer;				// タイマー
	CSceneBillBoard				*m_pBillBoard;

	EFFECTTEX					m_TexType;
};
#endif
