//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "billboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULEET_TEXTURE_000 "data/TEXTURE/bullet000.png"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CBullet : public CBillBoard
{// 派生させる時は : public ～を後ろにつけてやる
public:
	CBullet();
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CBullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// 共有テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXVECTOR3				m_pos;			// 位置
	D3DXVECTOR3				m_move;			// 移動量
	int						m_nLife;
};
#endif