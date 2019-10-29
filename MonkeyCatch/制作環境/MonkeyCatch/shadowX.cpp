//=============================================================================
//
// �I�u�W�F�N�g���� [object.cpp]
// Author : �|���j
//
//=============================================================================
#include "shadowX.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"

#include "shadow.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "tutorial.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 *CShadowX::m_pTexture = NULL;
LPD3DXMESH CShadowX::m_pMesh = NULL;
LPD3DXBUFFER CShadowX::m_pBuffMat = NULL;
DWORD CShadowX::m_nNumMat = NULL;
CPlayer * CShadowX::m_pPlayer = NULL;
CEnemy * CShadowX::m_pEnemy = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShadowX::CShadowX():CSceneX(4)
{
	m_pVtxBuff = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShadowX::~CShadowX()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CShadowX::Init(D3DXVECTOR3 pos)
{
	CSceneX::BindModelTex(m_pTexture, m_pMesh, m_pBuffMat, m_nNumMat);
	CSceneX::Init(pos);

	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �I�u�W�F�N�g�̃^�C�v�̐ݒ�
	SetObjType(CScene::OBJTYPE_OBJECT);

	// ���f��������
	m_pos = pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �F
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CShadowX::Uninit(void)
{
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

	//CSceneX::Uninit();

	// �I�u�W�F�N�g(�������g)�̔j��
	Release();

}
//=============================================================================
// �X�V����
//=============================================================================
void CShadowX::Update(void)
{
	// ���[�h�̎擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	if (mode == CManager::MODE_GAME)
	{// ���[�h���Q�[��
		m_pPlayer = CGame::GetPlayer();

		if (m_pPlayer != NULL)
		{
			D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();
			CSceneX::SetPosition(PlayerPos);
		}
	}

	if (mode == CManager::MODE_TUTORIAL)
	{//�@���[�h���`���[�g���A��
		m_pPlayer = CTutorial::GetPlayer();

		if (m_pPlayer != NULL)
		{
			D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();
			CSceneX::SetPosition(PlayerPos);
		}
	}

	//CDebugProc::Print(1, "���f�� : %.1f,%.1f,%.1f\n", m_pos.x, m_pos.y, m_pos.z);

	//// �f�o�b�O�\��
	//CDebugProc::Print(1, "�u���b�N��MAX : %.1f,%.1f,%.1f\n",m_VtxMax.x, m_VtxMax.y, m_VtxMax.z);
	//CDebugProc::Print(1, "�u���b�N��MIN : %.1f,%.1f,%.1f\n", m_VtxMin.x, m_VtxMin.y, m_VtxMin.z);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CShadowX::Draw(void)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �X�e���V���e�X�g��L��
	pDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);			// �X�e���V���o�b�t�@�ɏ�������

	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_ZERO);		// �X�e���V���e�X�g��Z�e�X�g�����i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);		// �X�e���V���e�X�g���i��Z�e�X�g���s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);		// �X�e���V���e�X�g�s���i

//#ifdef _DEBUG
//	// �L�[�{�[�h�̎擾
//	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
//	// �J�����O
//	if (pInputKeyboard->GetPress(DIK_C) == true)
//	{// F1����������ON
//		pDevice->SetRenderState(D3DRS_FILLMODE, 2);
//	}
//#endif

	// �\�ʂ̃J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);

	// �e�̃��f���`��
	CSceneX::Draw();

	pDevice->SetRenderState(D3DRS_STENCILREF, 1);						// �X�e���V���Q�ƒl
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// �X�e���V���o�b�t�@�ɏ�������

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);		// �X�e���V���e�X�g��Z�e�X�g�����i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// �X�e���V���e�X�g���i��Z�e�X�g���s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// �X�e���V���e�X�g�s���i

	// ���ʂ̃J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// �e�̃��f���`��
	CSceneX::Draw();

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000f);

	pDevice->SetRenderState(D3DRS_STENCILREF, 2);						// �X�e���V���Q�ƒl
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// �X�e���V���o�b�t�@�ɏ�������

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);		// �X�e���V���e�X�g��Z�e�X�g�����i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// �X�e���V���e�X�g���i��Z�e�X�g���s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// �X�e���V���e�X�g�s���i

	// ��ʂ������h��Ԃ�
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �X�e���V���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}
//=============================================================================
// ����
//=============================================================================
CShadowX * CShadowX::Create(D3DXVECTOR3 pos)
{
	CShadowX *pObject = NULL;

	if (pObject == NULL)
	{
		pObject = new CShadowX;

		pObject->Init(pos);
	}
	return pObject;
}
//=============================================================================
// ���f���̓ǂݍ���
//=============================================================================
HRESULT CShadowX::LoadX(void)
{
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(SHADOW_MODEL_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

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
void CShadowX::UnloadX(void)
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
}