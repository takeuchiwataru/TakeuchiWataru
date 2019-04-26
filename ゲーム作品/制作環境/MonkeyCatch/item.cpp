//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "item.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"

#include "shadow.h"

#include "game.h"
#include "life.h"
#include "player.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
////LPDIRECT3DTEXTURE9 *CItem::m_apTexture[ITEMTYPE_MAX] = {};
//LPD3DXMESH CItem::m_apMesh[ITEMTYPE_MAX] = {};
//LPD3DXBUFFER CItem::m_apBuffMat[ITEMTYPE_MAX] = {};
//DWORD CItem::m_anNumMat[ITEMTYPE_MAX] = {};

LPDIRECT3DTEXTURE9 *CItem::m_pTexture = NULL;
LPD3DXMESH CItem::m_pMesh = NULL;
LPD3DXBUFFER CItem::m_pBuffMat = NULL;
DWORD CItem::m_nNumMat = NULL;
CShadow * CItem::m_pShadow = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CItem::CItem()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_bUse = false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CItem::~CItem()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, ITEMTYPE type)
{
	CSceneX::BindModelTex(m_pTexture, m_pMesh, m_pBuffMat, m_nNumMat);
	CSceneX::Init(pos);

	//if (m_type == ITEMTYPE_BANANA)
	//{
	//	CSceneX::BindModelTex(m_pTexture, m_pMesh, m_pBuffMat, m_nNumMat);
	//	CSceneX::Init(pos);
	//	//CSceneX::BindModel(m_apMesh[0], m_apBuffMat[0], m_anNumMat[0]);
	//	//CSceneX::Init(pos);
	//}
	//if (m_type == ITEMTYPE_001)
	//{
	//	CSceneX::BindModel(m_apMesh[1], m_apBuffMat[1], m_anNumMat[1]);
	//	CSceneX::Init(pos);
	//}

	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// オブジェクトのタイプの設定
	SetObjType(CScene::OBJTYPE_ITEM);

	// モデル初期化
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = type;
	m_bUse = false;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CItem::Uninit(void)
{
	if (m_pShadow != NULL)
	{// 影がNULLじゃなかったらNULLにする
		m_pShadow = NULL;
	}

	if (m_pTexture != NULL)
	{// (家)
		for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
		{// (家具)
			if (m_pTexture[nCnt] != NULL)
			{// テクスチャ破棄
				m_pTexture[nCnt]->Release();
				m_pTexture[nCnt] = NULL;
			}
		}
	}

	// メモリの開放(解体)
	delete[] m_pTexture;
	// NULLを入れる(更地)
	m_pTexture = NULL;

	// オブジェクト(自分自身)の破棄
	Release();
}
//=============================================================================
// 更新処理
//=============================================================================
void CItem::Update(void)
{
	m_rot.y += 0.02f;

	if (m_bUse == true)
	{// アイテムを取ったら
		Uninit();
	}

	// 回転を反映
	CSceneX::SetPosition(m_pos, m_rot);
}
//=============================================================================
// 描画処理
//=============================================================================
void CItem::Draw(void)
{
	CSceneX::Draw();
}
//=============================================================================
// 生成
//=============================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, ITEMTYPE type)
{
	CItem *pItem = NULL;

	if (pItem == NULL)
	{
		pItem = new CItem;

		pItem->Init(pos,type);

		if (m_pShadow == NULL)
		{// 影の生成
			m_pShadow = CShadow::Create(D3DXVECTOR3(pos.x, pos.y + ITEM_SHADOWPOS, pos.z));
		}
	}
	return pItem;
}
//=============================================================================
// モデルの読み込み
//=============================================================================
HRESULT CItem::LoadX(void)
{
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(ITEM_MODEL_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	//// Xファイルの読み込み
	//D3DXLoadMeshFromX(ITEM_MODEL_NAME000,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&m_apBuffMat[0],
	//	NULL,
	//	&m_anNumMat[0],
	//	&m_apMesh[0]);

	//D3DXLoadMeshFromX(ITEM_MODEL_NAME000,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&m_apBuffMat[1],
	//	NULL,
	//	&m_anNumMat[1],
	//	&m_apMesh[1]);

	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		m_pTexture[nCntMat] = NULL;

		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// テクスチャの生成
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntMat]);
		}
	}

	return S_OK;
}
//=============================================================================
// モデルの破棄
//=============================================================================
void CItem::UnloadX(void)
{
	// メッシュの開放
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// マテリアルの開放
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	//for (int nCnt = 0; nCnt < ITEMTYPE_MAX; nCnt++)
	//{// アイテムの種類分繰り返し	
	//	if (m_apMesh[nCnt] != NULL)
	//	{// メッシュの開放
	//		m_apMesh[nCnt]->Release();
	//		m_apMesh[nCnt] = NULL;
	//	}
	//	if (m_apBuffMat[nCnt] != NULL)
	//	{// マテリアルの開放
	//		m_apBuffMat[nCnt]->Release();
	//		m_apBuffMat[nCnt] = NULL;
	//	}
	//}
}
//=============================================================================
// 当たり判定
//=============================================================================
bool CItem::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove,D3DXVECTOR3 *pVtxMax, D3DXVECTOR3 *pVtxMin)
{
	D3DXVECTOR3 VtxMax = CSceneX::GetMax();
	D3DXVECTOR3 VtxMin = CSceneX::GetMin();

	bool bHit = false;		// 当たったかどうか

	// プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();

	if (pPos->y + pVtxMax->y > m_pos.y + VtxMin.y && pPos->y + pVtxMin->y < m_pos.y + VtxMax.y)
	{// モデルの高さ分
		if (pPos->x + pVtxMax->x > m_pos.x + VtxMin.x && pPos->x + pVtxMin->x < m_pos.x + VtxMax.x)
		{// Z面の判定
			if (pPosold->z + pVtxMin->z >= m_pos.z + VtxMax.z && m_pos.z + VtxMax.z >= pPos->z + pVtxMin->z)
			{// 奧の判定
				pPos->z = pPosold->z;
				bHit = true;
				m_bUse = true;
				m_pShadow->DeleteShadow();
				//pPlayer->Hit(1);
			}
			if (pPosold->z + pVtxMax->z <= m_pos.z + VtxMin.z && m_pos.z + VtxMin.z <= pPos->z + pVtxMax->z)
			{// 手前の判定
				pPos->z = pPosold->z;
				bHit = true;
				m_bUse = true;
				m_pShadow->DeleteShadow();
				//pPlayer->Hit(1);
			}
		}

		if (pPos->z + pVtxMax->z > m_pos.z + VtxMin.z && pPos->z + pVtxMin->z < m_pos.z + VtxMax.z)
		{// X面の判定
			if (pPosold->x + pVtxMin->x >= m_pos.x + VtxMax.x && m_pos.x + VtxMax.x >= pPos->x + pVtxMin->x)
			{// 右面の判定		
				pPos->x = pPosold->x;
				bHit = true;
				m_bUse = true;
				m_pShadow->DeleteShadow();
				//pPlayer->Hit(1);
			}
			if (pPosold->x + pVtxMax->x <= m_pos.x + VtxMin.x && m_pos.x + VtxMin.x <= pPos->x + pVtxMax->x)
			{// 左面の判定
				pPos->x = pPosold->x;
				bHit = true;
				m_bUse = true;
				m_pShadow->DeleteShadow();
				//pPlayer->Hit(1);
			}
		}
	}
	if (pPos->z > m_pos.z + VtxMin.z + pVtxMin->z && pPos->z < m_pos.z + VtxMax.z + pVtxMax->z &&
		pPos->x > m_pos.x + VtxMin.x + pVtxMin->x && pPos->x < m_pos.x + VtxMax.x + pVtxMax->x)
	{// モデルの横
		if (pPosold->y >= m_pos.y + VtxMax.y && pPos->y <= m_pos.y + VtxMax.y)
		{// 上の判定
			pPos->y = pPosold->y;
			bHit = true;
			m_bUse = true;
			m_pShadow->DeleteShadow();
		}
	}
	return bHit;
}
