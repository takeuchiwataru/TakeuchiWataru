//=============================================================================
//
// �e(�~��)�̏��� [shadowX.h]
// Author : �|���j
//
//=============================================================================
#ifndef _SHADOWX_H_
#define _SHADOWX_H_

#include "main.h"
#include "sceneX.h"

class CPlayer;
class CEnemy;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SHADOW_MODEL_NAME000 "data/MODEL/shadow000.x"
#define SHADOW_MOVE_SPEED (2.0f)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CShadowX : public CSceneX
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:

	typedef enum
	{// �I�u�W�F�N�g�̎��
		OBJECTTYPE_TREE = 0,
		OBJECTTYPE_MAX
	}OBJECTTYPE;

	CShadowX();
	~CShadowX();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CShadowX * Create(D3DXVECTOR3 pos);
	static HRESULT LoadX(void);
	static void UnloadX(void);

	// �ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9		*m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH		m_pMesh;				// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER		m_pBuffMat;				// �}�e���A�����ւ̃|�C���^
	static DWORD			m_nNumMat;				// �}�e���A�����̐�
	static CPlayer * m_pPlayer;
	static CEnemy * m_pEnemy;

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;					// �ʒu
	D3DXVECTOR3				m_posold;				// �ʒu
	D3DXVECTOR3				m_rot;					// ����
	D3DXVECTOR3				m_move;					// �ړ�
	D3DXMATRIX				m_mtxWorld;				// ���[���h�}�g���b�N�X
	OBJECTTYPE				m_type;					// ���
	D3DXMATRIX m_mtxRot, m_mtxTrans;			// �v�Z�p�}�g���b�N�X
	float m_fDest;								// �ړI�̊p�x
	float m_fDiff;								// �p�x�̍���

};
#endif