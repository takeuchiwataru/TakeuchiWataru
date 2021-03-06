//=============================================================================
//
// フレーム処理 [logo.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "frame.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CFrame::m_apTexture[FRAMETYPE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CFrame::CFrame() :CLogo(3)
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CFrame::~CFrame()
{

}
//=============================================================================
// フレーム初期化処理
//=============================================================================
HRESULT CFrame::Init(D3DXVECTOR3 pos,FRAMETYPE type)
{
	CLogo::Init(pos);

	m_nType = type;

	if (m_nType == FRAMETYPE_SCORE)
	{// スコアフレーム
		CLogo::SetPosition(pos, 260, 50);
	}
	if (m_nType == FRAMETYPE_TIMER)
	{// タイマーフレーム
		CLogo::SetPosition(pos, 100, 50);
	}

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_FRAME);


	return S_OK;
}
//=============================================================================
// フレーム終了処理
//=============================================================================
void CFrame::Uninit(void)
{
	CLogo::Uninit();
}
//=============================================================================
// フレーム更新処理
//=============================================================================
void CFrame::Update(void)
{

}
//=============================================================================
// フレーム描画処理
//=============================================================================
void CFrame::Draw(void)
{
	CLogo::Draw();
}
//=============================================================================
// 生成
//=============================================================================
CFrame * CFrame::Create(D3DXVECTOR3 pos,FRAMETYPE type)
{
	CFrame *pFrame = NULL;

	if (pFrame == NULL)
	{
		pFrame = new CFrame;

		if (pFrame != NULL)
		{
			pFrame->Init(pos, type);

			if (type == FRAMETYPE_TIMER)
			{// タイマーフレーム
				pFrame->BindTexture(CTexture::GetTexture(0));
			}
			if (type == FRAMETYPE_SCORE)
			{// スコアフレーム
				pFrame->BindTexture(CTexture::GetTexture(1));
			}
			//pFrame->BindTexture(m_apTexture[type]);

		}
	}
	return pFrame;
}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CFrame::Load(void)
{
	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, FRAME_TEXTURE000, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, FRAME_TEXTURE001, &m_apTexture[1]);

	return S_OK;
}
//=============================================================================
// テクスチャの破棄
//=============================================================================
void CFrame::Unload(void)
{
	for (int nCntTex = 0; nCntTex < FRAMETYPE_MAX; nCntTex++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
