//=============================================================================
//
// アイテム処理 [item.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "sceneX.h"

//*****************************************************************************
// 前方宣言 インクルードはいらない
//*****************************************************************************
class CShadow;
//class CLife;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ITEM_MODEL_NAME000 "data/MODEL/banana.x"
#define ITEM_MODEL_NAME001 "data/MODEL/box000.x"

#define ITEM_SHADOWPOS (0.3f)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CItem : public CSceneX
{// 派生させる時は : public ～を後ろにつけてやる
public:

	typedef enum
	{// オブジェクトの種類
		ITEMTYPE_BANANA = 0,
		ITEMTYPE_001,
		ITEMTYPE_MAX
	}ITEMTYPE;

	CItem();
	~CItem();
	HRESULT Init(D3DXVECTOR3 pos, ITEMTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMax, D3DXVECTOR3 *pVtxMin);

	// 静的メンバ関数
	static CItem * Create(D3DXVECTOR3 pos, ITEMTYPE type);
	static HRESULT LoadX(void);
	static void UnloadX(void);

	// 静的メンバ変数
	//static LPDIRECT3DTEXTURE9		*m_apTexture[ITEMTYPE_MAX];	// テクスチャへのポインタ
	//static LPD3DXMESH		m_apMesh[ITEMTYPE_MAX];			// メッシュ情報へのポインタ
	//static LPD3DXBUFFER		m_apBuffMat[ITEMTYPE_MAX];		// マテリアル情報へのポインタ
	//static DWORD			m_anNumMat[ITEMTYPE_MAX];		// マテリアル情報の数

	static LPDIRECT3DTEXTURE9		*m_pTexture;	// テクスチャへのポインタ
	static LPD3DXMESH		m_pMesh;				// メッシュ情報へのポインタ
	static LPD3DXBUFFER		m_pBuffMat;				// マテリアル情報へのポインタ
	static DWORD			m_nNumMat;				// マテリアル情報の数
	static CShadow * m_pShadow;

private:
	D3DXVECTOR3				m_pos;					// 位置
	D3DXVECTOR3				m_rot;					// 向き
	D3DXVECTOR3				m_move;					// 移動
	D3DXMATRIX				m_mtxWorld;				// ワールドマトリックス
	ITEMTYPE				m_type;					// 種類
	D3DXMATRIX m_mtxRot, m_mtxTrans;				// 計算用マトリックス
	bool					m_bUse;					// あるかないか
};
#endif