//=============================================================================
//
// ビルボード処理 [Billboard.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "billboard.h"
#include "manager.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BILLBOARD_TEXTURENAME000	 "data\\TEXTURE\\BILLBOARD\\tree000.png"		//テクスチャのファイル名
#define TEX_POS_X_INIT				(1.0f)								//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT				(1.0f)								//テクスチャ座標Vの初期位置
#define TEX_LEFT					(0.0f)								//テクスチャ座標U左
#define TEX_RIGHT					(1.0f)								//テクスチャ座標U右
#define TEX_TOP						(0.0f)								//テクスチャ座標V上
#define TEX_BOT						(1.0f)								//テクスチャ座標V下

//--------------------------------------------
//シーンビルボードクラス コンストラクタ
//--------------------------------------------
CSceneBillBoard::CSceneBillBoard() : CScene(5, CScene::OBJTYPE_BILLBOARD)
{
	//メンバ変数
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

	m_fWidth = 0;
	m_fHeight = 0;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtrxWorld);

}

//--------------------------------------------
//シーンビルボードクラス デストラクタ
//--------------------------------------------
CSceneBillBoard::~CSceneBillBoard()
{
}

//--------------------------------------------
//シーンビルボードの生成
//--------------------------------------------
CSceneBillBoard *CSceneBillBoard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight)
{
	CSceneBillBoard *pBillBoard;

	pBillBoard = new CSceneBillBoard;

	//値の代入
	pBillBoard->m_pos = pos;
	pBillBoard->m_move = move;
	pBillBoard->m_fHeight = fHeight;
	pBillBoard->m_fWidth = fWidth;

	pBillBoard->Init();

	return pBillBoard;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneBillBoard::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	BILLBOARD_TEXTURENAME000,
	//	&m_pTexture);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標 (サイズだけ決める)
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, 0.0f, 0.0f);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
	pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
	pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
	pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//オブジェクトタイプの設定
	CScene::SetObjType(OBJTYPE_BILLBOARD);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneBillBoard::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//自分を消す(シーン2Dを破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSceneBillBoard::Update(void)
{
	//位置更新
	m_pos += m_move;
}

//=============================================================================
// 描画処理
//=============================================================================
void CSceneBillBoard::Draw(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 Kyori = m_pos - pPlayer->GetPos();
	Kyori.z = abs(Kyori.z);

	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX  mtxView, mtxTrans;				//計算用マトリックス

	//現在のモードを取得
	CManager::MODE mode = CManager::GetMode();
	switch (mode)
	{
	case CManager::MODE_GAME:
		if (m_pos.z + 200 > pPlayer->GetPos().z)
		{
			if (Kyori.z < 10000)
			{


				//アルファテスト(透明色を描画しないように)
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
				pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
				pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

				if (GetObjType() == OBJTYPE_EFFECTADD)
				{
					//レンダーステートの設定を元に戻す
					pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

					//Zバッファの設定
					pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
					//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
					// αブレンディングを加算合成に設定
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				}

				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&m_mtrxWorld);
				D3DXMatrixIdentity(&mtxView);
				D3DXMatrixIdentity(&mtxTrans);

				//ビューマトリックスを取得
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				//逆行列を設定
				m_mtrxWorld._11 = mtxView._11;
				m_mtrxWorld._12 = mtxView._21;
				m_mtrxWorld._13 = mtxView._31;
				m_mtrxWorld._21 = mtxView._12;
				m_mtrxWorld._22 = mtxView._22;
				m_mtrxWorld._23 = mtxView._32;
				m_mtrxWorld._31 = mtxView._13;
				m_mtrxWorld._32 = mtxView._23;
				m_mtrxWorld._33 = mtxView._33;

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

				D3DXMatrixMultiply(&m_mtrxWorld, &m_mtrxWorld, &mtxTrans);
				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &m_mtrxWorld);
				//頂点バッファをデータストリームに設定
				pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
				//頂点フォーマットを設定
				pDevice->SetFVF(FVF_VERTEX_3D);

				//テクスチャの設定
				pDevice->SetTexture(0, m_pTexture);
				// ビルボードの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					0,	//開始する頂点のインデックス
					2); //描画するプリミティブ数

				//レンダーステートの設定を元に戻す
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

				if (GetObjType() == OBJTYPE_EFFECTADD)
				{
					//Zバッファをデフォルトの設定に戻す
					pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
					pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
					// αブレンディングを元に戻す
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				}
			}
		}
		break;
	case CManager::MODE_TITLE:

		//アルファテスト(透明色を描画しないように)
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (GetObjType() == OBJTYPE_EFFECTADD)
		{
			//レンダーステートの設定を元に戻す
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			//Zバッファの設定
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			// αブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtrxWorld);
		D3DXMatrixIdentity(&mtxView);
		D3DXMatrixIdentity(&mtxTrans);

		//ビューマトリックスを取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//逆行列を設定
		m_mtrxWorld._11 = mtxView._11;
		m_mtrxWorld._12 = mtxView._21;
		m_mtrxWorld._13 = mtxView._31;
		m_mtrxWorld._21 = mtxView._12;
		m_mtrxWorld._22 = mtxView._22;
		m_mtrxWorld._23 = mtxView._32;
		m_mtrxWorld._31 = mtxView._13;
		m_mtrxWorld._32 = mtxView._23;
		m_mtrxWorld._33 = mtxView._33;

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtrxWorld, &m_mtrxWorld, &mtxTrans);
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtrxWorld);
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
		//頂点フォーマットを設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);
		// ビルボードの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,	//開始する頂点のインデックス
			2); //描画するプリミティブ数

				//レンダーステートの設定を元に戻す
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		if (GetObjType() == OBJTYPE_EFFECTADD)
		{
			//Zバッファをデフォルトの設定に戻す
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			// αブレンディングを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
		break;
	case CManager::MODE_TUTORIAL:

		//アルファテスト(透明色を描画しないように)
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (GetObjType() == OBJTYPE_EFFECTADD)
		{
			//レンダーステートの設定を元に戻す
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			//Zバッファの設定
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			// αブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtrxWorld);
		D3DXMatrixIdentity(&mtxView);
		D3DXMatrixIdentity(&mtxTrans);

		//ビューマトリックスを取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//逆行列を設定
		m_mtrxWorld._11 = mtxView._11;
		m_mtrxWorld._12 = mtxView._21;
		m_mtrxWorld._13 = mtxView._31;
		m_mtrxWorld._21 = mtxView._12;
		m_mtrxWorld._22 = mtxView._22;
		m_mtrxWorld._23 = mtxView._32;
		m_mtrxWorld._31 = mtxView._13;
		m_mtrxWorld._32 = mtxView._23;
		m_mtrxWorld._33 = mtxView._33;

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtrxWorld, &m_mtrxWorld, &mtxTrans);
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtrxWorld);
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
		//頂点フォーマットを設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);
		// ビルボードの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,	//開始する頂点のインデックス
			2); //描画するプリミティブ数

				//レンダーステートの設定を元に戻す
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		if (GetObjType() == OBJTYPE_EFFECTADD)
		{
			//Zバッファをデフォルトの設定に戻す
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			// αブレンディングを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
		break;
	}
}

//=============================================================================
// ビルボードの位置設定処理
//=============================================================================
void CSceneBillBoard::Setpos(D3DXVECTOR3 pos)
{
	// シーンビルボードの位置を設定
	m_pos = pos;
}

void CSceneBillBoard::Set(float fWidth, float fHeight)
{

}

//=============================================================================
// ビルボードの設定処理
//=============================================================================
void CSceneBillBoard::SetBillboard(D3DXVECTOR3 pos, float fHeight, float fWidth)
{
	VERTEX_3D *pVtx;//頂点情報へのポインタ
					//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	m_pos = pos;

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(-fWidth, fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fWidth, fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fWidth, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fWidth, 0.0f, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}


//=============================================================================
//ビルボードテクスチャの設定
//=============================================================================
void CSceneBillBoard::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}

//=============================================================================
//ビルボード位置取得
//=============================================================================
D3DXVECTOR3 CSceneBillBoard::GetPos(void)
{
	return m_pos;
}

//=============================================================================
//ビルボード色設定
//=============================================================================
void CSceneBillBoard::SetCol(D3DXCOLOR col)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラー
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//ビルボード頂点取得
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CSceneBillBoard::GetVtx(void)
{
	return m_pVtxBuff;
}
