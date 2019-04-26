//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : �|���j
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
// �ÓI�����o�ϐ�
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
// �R���X�g���N�^
//=============================================================================
CItem::CItem()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_bUse = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItem::~CItem()
{

}
//=============================================================================
// ����������
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

	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �I�u�W�F�N�g�̃^�C�v�̐ݒ�
	SetObjType(CScene::OBJTYPE_ITEM);

	// ���f��������
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = type;
	m_bUse = false;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CItem::Uninit(void)
{
	if (m_pShadow != NULL)
	{// �e��NULL����Ȃ�������NULL�ɂ���
		m_pShadow = NULL;
	}

	if (m_pTexture != NULL)
	{// (��)
		for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
		{// (�Ƌ�)
			if (m_pTexture[nCnt] != NULL)
			{// �e�N�X�`���j��
				m_pTexture[nCnt]->Release();
				m_pTexture[nCnt] = NULL;
			}
		}
	}

	// �������̊J��(���)
	delete[] m_pTexture;
	// NULL������(�X�n)
	m_pTexture = NULL;

	// �I�u�W�F�N�g(�������g)�̔j��
	Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CItem::Update(void)
{
	m_rot.y += 0.02f;

	if (m_bUse == true)
	{// �A�C�e�����������
		Uninit();
	}

	// ��]�𔽉f
	CSceneX::SetPosition(m_pos, m_rot);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CItem::Draw(void)
{
	CSceneX::Draw();
}
//=============================================================================
// ����
//=============================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, ITEMTYPE type)
{
	CItem *pItem = NULL;

	if (pItem == NULL)
	{
		pItem = new CItem;

		pItem->Init(pos,type);

		if (m_pShadow == NULL)
		{// �e�̐���
			m_pShadow = CShadow::Create(D3DXVECTOR3(pos.x, pos.y + ITEM_SHADOWPOS, pos.z));
		}
	}
	return pItem;
}
//=============================================================================
// ���f���̓ǂݍ���
//=============================================================================
HRESULT CItem::LoadX(void)
{
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(ITEM_MODEL_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	//// X�t�@�C���̓ǂݍ���
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
			// �e�N�X�`���̐���
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntMat]);
		}
	}

	return S_OK;
}
//=============================================================================
// ���f���̔j��
//=============================================================================
void CItem::UnloadX(void)
{
	// ���b�V���̊J��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���̊J��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	//for (int nCnt = 0; nCnt < ITEMTYPE_MAX; nCnt++)
	//{// �A�C�e���̎�ޕ��J��Ԃ�	
	//	if (m_apMesh[nCnt] != NULL)
	//	{// ���b�V���̊J��
	//		m_apMesh[nCnt]->Release();
	//		m_apMesh[nCnt] = NULL;
	//	}
	//	if (m_apBuffMat[nCnt] != NULL)
	//	{// �}�e���A���̊J��
	//		m_apBuffMat[nCnt]->Release();
	//		m_apBuffMat[nCnt] = NULL;
	//	}
	//}
}
//=============================================================================
// �����蔻��
//=============================================================================
bool CItem::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove,D3DXVECTOR3 *pVtxMax, D3DXVECTOR3 *pVtxMin)
{
	D3DXVECTOR3 VtxMax = CSceneX::GetMax();
	D3DXVECTOR3 VtxMin = CSceneX::GetMin();

	bool bHit = false;		// �����������ǂ���

	// �v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();

	if (pPos->y + pVtxMax->y > m_pos.y + VtxMin.y && pPos->y + pVtxMin->y < m_pos.y + VtxMax.y)
	{// ���f���̍�����
		if (pPos->x + pVtxMax->x > m_pos.x + VtxMin.x && pPos->x + pVtxMin->x < m_pos.x + VtxMax.x)
		{// Z�ʂ̔���
			if (pPosold->z + pVtxMin->z >= m_pos.z + VtxMax.z && m_pos.z + VtxMax.z >= pPos->z + pVtxMin->z)
			{// ���̔���
				pPos->z = pPosold->z;
				bHit = true;
				m_bUse = true;
				m_pShadow->DeleteShadow();
				//pPlayer->Hit(1);
			}
			if (pPosold->z + pVtxMax->z <= m_pos.z + VtxMin.z && m_pos.z + VtxMin.z <= pPos->z + pVtxMax->z)
			{// ��O�̔���
				pPos->z = pPosold->z;
				bHit = true;
				m_bUse = true;
				m_pShadow->DeleteShadow();
				//pPlayer->Hit(1);
			}
		}

		if (pPos->z + pVtxMax->z > m_pos.z + VtxMin.z && pPos->z + pVtxMin->z < m_pos.z + VtxMax.z)
		{// X�ʂ̔���
			if (pPosold->x + pVtxMin->x >= m_pos.x + VtxMax.x && m_pos.x + VtxMax.x >= pPos->x + pVtxMin->x)
			{// �E�ʂ̔���		
				pPos->x = pPosold->x;
				bHit = true;
				m_bUse = true;
				m_pShadow->DeleteShadow();
				//pPlayer->Hit(1);
			}
			if (pPosold->x + pVtxMax->x <= m_pos.x + VtxMin.x && m_pos.x + VtxMin.x <= pPos->x + pVtxMax->x)
			{// ���ʂ̔���
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
	{// ���f���̉�
		if (pPosold->y >= m_pos.y + VtxMax.y && pPos->y <= m_pos.y + VtxMax.y)
		{// ��̔���
			pPos->y = pPosold->y;
			bHit = true;
			m_bUse = true;
			m_pShadow->DeleteShadow();
		}
	}
	return bHit;
}
