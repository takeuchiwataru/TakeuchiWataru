//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "model.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CModel::CModel()
{
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

	//m_pMesh = NULL;
	//m_pBuffMat = NULL;
	//m_nNumMat = NULL;

	m_pParent = NULL;		// 親モデルのポインタ
}
//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModel::Init(D3DXVECTOR3 pos)
{
	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	//int nNumVtex;			// 頂点数
	//DWORD sizeFvF;		// 頂点フォーマットのサイズ
	//BYTE *pVtxBuff;		// 頂点バッファへのポインタ

	// モデル初期化
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
	m_VtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);

	//// 頂点数を取得
	//nNumVtex = m_pMesh->GetNumVertices();

	//// 頂点フォーマットのサイズを取得
	//sizeFvF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//// 頂点バッファをロック
	//m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
	//{
	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
	//	if (m_VtxMinModel.x >= vtx.x)
	//	{
	//		m_VtxMinModel.x = vtx.x;
	//	}
	//	if (m_VtxMinModel.y >= vtx.y)
	//	{
	//		m_VtxMinModel.y = vtx.y;
	//	}
	//	if (m_VtxMinModel.z >= vtx.z)
	//	{
	//		m_VtxMinModel.z = vtx.z;
	//	}

	//	if (m_VtxMaxModel.x <= vtx.x)
	//	{
	//		m_VtxMaxModel.x = vtx.x;
	//	}
	//	if (m_VtxMaxModel.y <= vtx.y)
	//	{
	//		m_VtxMaxModel.y = vtx.y;
	//	}
	//	if (m_VtxMaxModel.z <= vtx.z)
	//	{
	//		m_VtxMaxModel.z = vtx.z;
	//	}
	//	pVtxBuff += sizeFvF;
	//}
	//// 頂点バッファをアンロック
	//m_pMesh->UnlockVertexBuffer();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CModel::Uninit(void)
{
	//// メッシュの開放
	//if (m_pMesh != NULL)
	//{
	//	m_pMesh->Release();
	//	m_pMesh = NULL;
	//}

	//// マテリアルの開放
	//if (m_pBuffMat != NULL)
	//{
	//	m_pBuffMat->Release();
	//	m_pBuffMat = NULL;
	//}
}
//=============================================================================
// 更新処理
//=============================================================================
void CModel::Update(void)
{

}
//=============================================================================
// 描画処理
//=============================================================================
void CModel::Draw(void)
{
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DXMATRIX	mtxParent;						// 親のマトリックス

	CManager manager;	//インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// 親のマトリックスを反映
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャ
		pDevice->SetTexture(0, m_pTexture);

		// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}
//=============================================================================
// 生成
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos)
{
	CModel *pModel = NULL;

	if (pModel == NULL)
	{
		pModel = new CModel;

		pModel->Init(pos);
	}
	return pModel;
}
//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}
//=============================================================================
// テクスチャの割り当て
//=============================================================================
void CModel::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//=============================================================================
// モデルの割り当て
//=============================================================================
void CModel::BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD pNumMat)
{
	m_pMesh = pMesh;
	m_pBuffMat = pBuffMat;
	m_nNumMat = pNumMat;
}

//=============================================================================
// 頂点バッファの取得
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CModel::GetVtxBuff(void)
{
	return m_pVtxBuff;
}
//=============================================================================
// 親の設置
//=============================================================================
void CModel::SetParent(CModel * pModel)
{
	m_pParent = pModel;
}
//=============================================================================
// 回転の設置
//=============================================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//=============================================================================
// 位置の設置
//=============================================================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//=============================================================================
// ワールドマトリックスの取得
//=============================================================================
D3DXMATRIX &CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}


