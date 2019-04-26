//=============================================================================
//
// �A�C�e������ [item.h]
// Author : �|���j
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "sceneX.h"

//*****************************************************************************
// �O���錾 �C���N���[�h�͂���Ȃ�
//*****************************************************************************
class CShadow;
//class CLife;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ITEM_MODEL_NAME000 "data/MODEL/banana.x"
#define ITEM_MODEL_NAME001 "data/MODEL/box000.x"

#define ITEM_SHADOWPOS (0.3f)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CItem : public CSceneX
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:

	typedef enum
	{// �I�u�W�F�N�g�̎��
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

	// �ÓI�����o�֐�
	static CItem * Create(D3DXVECTOR3 pos, ITEMTYPE type);
	static HRESULT LoadX(void);
	static void UnloadX(void);

	// �ÓI�����o�ϐ�
	//static LPDIRECT3DTEXTURE9		*m_apTexture[ITEMTYPE_MAX];	// �e�N�X�`���ւ̃|�C���^
	//static LPD3DXMESH		m_apMesh[ITEMTYPE_MAX];			// ���b�V�����ւ̃|�C���^
	//static LPD3DXBUFFER		m_apBuffMat[ITEMTYPE_MAX];		// �}�e���A�����ւ̃|�C���^
	//static DWORD			m_anNumMat[ITEMTYPE_MAX];		// �}�e���A�����̐�

	static LPDIRECT3DTEXTURE9		*m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH		m_pMesh;				// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER		m_pBuffMat;				// �}�e���A�����ւ̃|�C���^
	static DWORD			m_nNumMat;				// �}�e���A�����̐�
	static CShadow * m_pShadow;

private:
	D3DXVECTOR3				m_pos;					// �ʒu
	D3DXVECTOR3				m_rot;					// ����
	D3DXVECTOR3				m_move;					// �ړ�
	D3DXMATRIX				m_mtxWorld;				// ���[���h�}�g���b�N�X
	ITEMTYPE				m_type;					// ���
	D3DXMATRIX m_mtxRot, m_mtxTrans;				// �v�Z�p�}�g���b�N�X
	bool					m_bUse;					// ���邩�Ȃ���
};
#endif