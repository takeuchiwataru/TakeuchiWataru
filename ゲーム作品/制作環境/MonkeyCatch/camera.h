//=============================================================================
//
// �J�������� [camera.h]
// Author : �|���j
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �O���錾 �C���N���[�h�͂���Ȃ�
//*****************************************************************************
class CPlayer;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_MOVE (2.0f)
#define ANGLE_VIEW (45.0f)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCamera
{
public:
	CCamera();
	~CCamera();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetCamera(void);

private:
	typedef enum
	{// �J�����̏��
		CAMERASTATE_NORMAL = 0, // �ʏ�
		CAMERASTATE_MOVE,       // �ړ�
		CAMERASTATE_SPIN,       // ����
		CAMERASTATE_MAX
	}CAMERASTATE;

	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXVECTOR3 m_rot;			// ����
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_posVDest;		// �ړI�̎��_
	D3DXVECTOR3 m_posRDest;		// �ړI�̒����_
	D3DXVECTOR3 m_posVAdd;		// �ړI�̍��W
	D3DXVECTOR3 m_posRAdd;		// �ړI�̍��W
	D3DXVECTOR3 m_rotDest;		// �ړI�̌���

	float m_rotDiff;			// �����̍���
	D3DXVECTOR3 m_fLength;		// ����
	CAMERASTATE m_state;		// ���
	D3DVIEWPORT9 m_ViewPort;	// �r���[�|�[�g

	static CPlayer *m_pPlayer;
	static CPlayer *m_pPlayerT;
};
#endif