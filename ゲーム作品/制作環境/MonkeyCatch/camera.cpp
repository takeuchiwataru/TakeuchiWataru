//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"

#include "game.h"
#include "tutorial.h"
#include "player.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CPlayer *CCamera::m_pPlayer = NULL;
CPlayer *CCamera::m_pPlayerT = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_rotDiff = 0.0f;
	m_fLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = CAMERASTATE_NORMAL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// カメラの初期化処理
//=============================================================================
void CCamera::Init(void)
{

	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRAdd = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_rotDiff = 0.0f;
	m_fLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = CAMERASTATE_NORMAL;

	// ビューポートの設定
	m_ViewPort.X = 0;					// x座標左端
	m_ViewPort.Y = 0;					// y座標上端
	m_ViewPort.Width = SCREEN_WIDTH;	// x座標右端
	m_ViewPort.Height = SCREEN_HEIGHT;	// x座標下端
	m_ViewPort.MinZ = 0.0f;				// 手前
	m_ViewPort.MaxZ = 1.0f;				// 奥

	// モードの取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	if (mode == CManager::MODE_GAME || mode == CManager::MODE_TUTORIAL)
	{// モードがゲーム or チュートリアル
		m_fLength.x = 250;
		m_fLength.y = 100;
		m_fLength.z = 250;
	}
	else if (mode == CManager::MODE_TITLE || mode == CManager::MODE_RANKING || mode == CManager::MODE_RESULT)
	{// モードがタイトル or ランキング or リザルト
		m_fLength.x = 400;
		m_fLength.y = 0;
		m_fLength.z = 400;

		m_posR = D3DXVECTOR3(750.0f, 50.0f, -750.0f);       // フィールドの中心に注視点の設定
	}

	m_posV.x = m_posR.x + sinf(m_rot.y) * m_fLength.x;
	m_posV.y = m_posR.y + cosf(m_rot.y) * m_fLength.y;
	m_posV.z = m_posR.z + cosf(m_rot.y) * m_fLength.z;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::Update(void)
{
	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// ジョイパッドの取得
	CInputJoyPad *pInputJoyPad = CManager::GetJoyPad();

	// モードの取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	if (mode == CManager::MODE_TITLE || mode == CManager::MODE_RANKING)
	{// モードがタイトルだったら
		m_rot.y += D3DX_PI / 1200;
		if (m_rot.y >= D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
		m_posV.x = m_posR.x + sinf(m_rot.y) * m_fLength.x;
		m_posV.z = m_posR.z + cosf(m_rot.y) * m_fLength.z;
	}

	if (mode == CManager::MODE_GAME)
	{// モードがゲーム
		// プレイヤーの取得
		m_pPlayer = CGame::GetPlayer();
		if (m_pPlayer != NULL)
		{
			D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();
			D3DXVECTOR3 PlayerRot = m_pPlayer->GetRot();
			D3DXVECTOR3 PlayerMove = m_pPlayer->GetMove();

			// 視点設定
			m_posVDest.x = (PlayerPos.x + (3.0f * PlayerMove.x)) - sinf(m_rot.y) * m_fLength.x;		// 目的の視点を設定
			m_posVDest.y = (PlayerPos.y + m_posVAdd.y) + cosf(0.0f) * m_fLength.y;					// 目的の視点を設定
			m_posVDest.z = (PlayerPos.z + (3.0f * PlayerMove.z)) - cosf(m_rot.y) * m_fLength.z;		// 目的の視点を設定

			// 注視点設定
			m_posRDest.x = (PlayerPos.x + (3.0f * PlayerMove.x)) + sinf(PlayerRot.y + D3DX_PI) * ((PlayerMove.x * PlayerMove.x) + ((PlayerMove.x * PlayerMove.x)));	// 目的の注視点を設定
			m_posRDest.y = (PlayerPos.y + m_posRAdd.y);																										// 目的の注視点を設定
			m_posRDest.z = (PlayerPos.z + (3.0f * PlayerMove.z)) + cosf(PlayerRot.y + D3DX_PI) * ((PlayerMove.z * PlayerMove.z) + ((PlayerMove.z * PlayerMove.z)));	// 目的の注視点を設定

			m_posV.x += (m_posVDest.x - m_posV.x) * 0.2f;	// 現在の視点を設定
			m_posV.y += (m_posVDest.y - m_posV.y) * 0.2f;	// 現在の視点を設定
			m_posV.z += (m_posVDest.z - m_posV.z) * 0.2f;	// 現在の視点を設定

			m_posR.x += (m_posRDest.x - m_posR.x) * 0.20f;	// 現在の注視点を設定
			m_posR.y += (m_posRDest.y - m_posR.y) * 0.20f;	// 現在の注視点を設定
			m_posR.z += (m_posRDest.z - m_posR.z) * 0.20f;	// 現在の注視点を設定

			if (pInputJoyPad->GetPress(CInputJoyPad::DIJS_BUTTON_24) == true || pInputKeyboard->GetPress(DIK_Q) == true)
			{// 右スティックを左に倒したら
				m_rot.y -= D3DX_PI / 120;
				if (m_rot.y <= -D3DX_PI)
				{
					m_rot.y = D3DX_PI;
				}
			}
			else if (pInputJoyPad->GetPress(CInputJoyPad::DIJS_BUTTON_26) == true || pInputKeyboard->GetPress(DIK_E) == true)
			{// 右スティックを右に倒したら	
				m_rot.y += D3DX_PI / 120;
				if (m_rot.y >= D3DX_PI)
				{
					m_rot.y = -D3DX_PI;
				}
			}
		}
	}
	if (mode == CManager::MODE_TUTORIAL)
	{// モードがチュートリアル
		// プレイヤーの取得
		m_pPlayerT = CTutorial::GetPlayer();
		if (m_pPlayerT != NULL)
		{
			D3DXVECTOR3 PlayerPos = m_pPlayerT->GetPos();
			D3DXVECTOR3 PlayerRot = m_pPlayerT->GetRot();
			D3DXVECTOR3 PlayerMove = m_pPlayerT->GetMove();

			// 視点設定
			m_posVDest.x = (PlayerPos.x + (3.0f * PlayerMove.x)) - sinf(m_rot.y) * m_fLength.x;		// 目的の視点を設定
			m_posVDest.y = (PlayerPos.y + m_posVAdd.y) + cosf(0.0f) * m_fLength.y;			// 目的の視点を設定
			m_posVDest.z = (PlayerPos.z + (3.0f * PlayerMove.z)) - cosf(m_rot.y) * m_fLength.z;		// 目的の視点を設定

			// 注視点設定
			m_posRDest.x = (PlayerPos.x + (3.0f * PlayerMove.x)) + sinf(PlayerRot.y + D3DX_PI) * ((PlayerMove.x * PlayerMove.x) + ((PlayerMove.x * PlayerMove.x)));	// 目的の注視点を設定
			m_posRDest.y = (PlayerPos.y + m_posRAdd.y);																										// 目的の注視点を設定
			m_posRDest.z = (PlayerPos.z + (3.0f * PlayerMove.z)) + cosf(PlayerRot.y + D3DX_PI) * ((PlayerMove.z * PlayerMove.z) + ((PlayerMove.z * PlayerMove.z)));	// 目的の注視点を設定

			m_posV.x += (m_posVDest.x - m_posV.x) * 0.2f;	// 現在の視点を設定
			m_posV.y += (m_posVDest.y - m_posV.y) * 0.2f;	// 現在の視点を設定
			m_posV.z += (m_posVDest.z - m_posV.z) * 0.2f;	// 現在の視点を設定

			m_posR.x += (m_posRDest.x - m_posR.x) * 0.20f;	// 現在の注視点を設定
			m_posR.y += (m_posRDest.y - m_posR.y) * 0.20f;	// 現在の注視点を設定
			m_posR.z += (m_posRDest.z - m_posR.z) * 0.20f;	// 現在の注視点を設定

			if (pInputJoyPad->GetPress(CInputJoyPad::DIJS_BUTTON_24) == true || pInputKeyboard->GetPress(DIK_Q) == true)
			{// 右スティックを左に倒したら
				m_rot.y -= D3DX_PI / 120;
				if (m_rot.y <= -D3DX_PI)
				{
					m_rot.y = D3DX_PI;
				}
			}
			else if (pInputJoyPad->GetPress(CInputJoyPad::DIJS_BUTTON_26) == true || pInputKeyboard->GetPress(DIK_E) == true)
			{// 右スティックを右に倒したら	
				m_rot.y += D3DX_PI / 120;
				if (m_rot.y >= D3DX_PI)
				{
					m_rot.y = -D3DX_PI;
				}
			}
		}
	}
	if (mode == CManager::MODE_RESULT)
	{// モードがリザルト
		m_rot.y -= D3DX_PI / 1200;
		if (m_rot.y >= D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
		m_posV.x = m_posR.x + sinf(m_rot.y) * m_fLength.x;
		m_posV.z = m_posR.z + cosf(m_rot.y) * m_fLength.z;
	}

	//CDebugProc::Print(1, "PosV:%.1f,%.1f,%.1f\n", m_posV.x, m_posV.y, m_posV.z);
}
//=============================================================================
// カメラの設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	CManager manager;	// インスタンス

	LPDIRECT3DDEVICE9 pDevice;	// デバイスの取得
	pDevice = manager.GetRenderer()->GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(ANGLE_VIEW),								// 画角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,													// 手前の位置
		10000.0f);												// 奥の位置

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//=============================================================================
// カメラの取得
//=============================================================================
D3DXVECTOR3 CCamera::GetCamera(void)
{
	return m_rot;
}

