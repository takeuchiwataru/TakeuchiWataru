//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �|���j
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �O���錾 �C���N���[�h�͂���Ȃ�
//*****************************************************************************
class CObject;
class CEnemy;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_MOVE_SPEED (2.0f)
#define PLAYER_RUN_SPEED (3.0f)
#define PLAYER_JUMP (8.0f)
#define MAX_PLAYER_MODEL (11)			// �v���C���[�̃p�[�c��
#define NUM_MAX_KEY (4)					// �L�[�ő吔
#define NUM_MAX_PLAYER_MOTION (5)		// ���[�V�����ő吔
#define PLAYER_OFFSET (2)
#define PLAYER_MAX_POS (1490)
#define PLAYER_MIN_POS (0)
#define ATTACK_COUNTER (35)				// �U����Ԃ̃J�E���^�[
#define P_MAX_PARTICLE (1)				// �p�[�e�B�N����
#define P_PARTICLE_LIFE (15)			// �p�[�e�B�N�����C�t
#define P_PARTICLE_RADIUS (15)			// �p�[�e�B�N���̑傫��

#define PLAYER_FILE ("data/TEXT/motion_player.txt")
#define NUM_MODEL "NUM_MODEL = "
#define MODEL_FILENAME   "MODEL_FILENAME = "
#define CHARACTERSET "CHARACTERSET"
#define END_CHARACTERSET "END_CHARACTERSET"
#define NUM_PARTS "NUM_PARTS = "
#define PARTSSET "PARTSSET"
#define END_PARTSSET "END_PARTSSET"
#define INDEX "INDEX = "
#define PARENT "PARENT = "
#define POS "POS = "
#define ROT "ROT = "

#define MOTIONSET "MOTIONSET"
#define END_MOTIONSET "END_MOTIONSET"
#define LOOP "LOOP = "
#define NUM_KEY "NUM_KEY = "
#define KEYSET "KEYSET"
#define END_KEYSET "END_KEYSET"
#define FRAME "FRAME = "
#define KEY "KEY"
#define END_KEY "END_KEY"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CPlayer : public CScene
{
public:
	typedef struct
	{// �L�[�ݒ�
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}P_KEY;

	typedef struct
	{// �L�[���
		int nFrame;
		P_KEY aKey[MAX_PLAYER_MODEL];
	}KEY_INFO;

	typedef struct
	{// ���[�V�������
		bool bLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[NUM_MAX_KEY];
	}MOTION_INFO;

	typedef enum
	{// �v���C���[�̏��
		PLAYERSTATE_NONE = 0,
		PLAYERSTATE_NORMAL,		// �ʏ�
		PLAYERSTATE_MOVE,		// �ړ�
		PLAYERSTATE_JUMP,		// �W�����v
		PLAYERSTATE_LANDING,	// ���n
		PLAYERSTATE_MUSIAMI,	// ����
		PLAYERSTATE_MAX
	}PLAYERSTATE;

	CPlayer();
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void UpdateTutorial(void);
	void Draw(void);
	void Move(void);

	void LoadMotion(void);
	void UpdateMotion(void);
	char *ReadLine(FILE * pFile, char *pDst);
	char *GetLineTop(char *pSrc);
	int PopString(char * pSrc, char * pDst);

	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetMove(void);
	PLAYERSTATE GetState(void);
	bool AttackCollision(D3DXVECTOR3 pos, float radius);

	// �ÓI�����o�֐�
	static CPlayer * Create(D3DXVECTOR3 pos);

	// �ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;							// ���L�e�N�X�`���̃|�C���^
	static LPD3DXMESH		m_apMesh[MAX_PLAYER_MODEL];				// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER		m_apBuffMat[MAX_PLAYER_MODEL];			// �}�e���A�����ւ̃|�C���^
	static DWORD			m_anNumMat[MAX_PLAYER_MODEL];			// �}�e���A�����̐�
	static CMeshOrbit * m_pMeshOrbit;
	static CObject * m_pObject;

private:
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_posold;						// �ʒu
	D3DXVECTOR3 m_move;							// �ړ�
	D3DXVECTOR3 m_rot;							// ����
	PLAYERSTATE m_state;						// ���
	D3DXVECTOR3	m_aPosOffset[MAX_PLAYER_MODEL];	// ���f���̃I�t�Z�b�g
	D3DXVECTOR3 m_aPos[MAX_PLAYER_MODEL];		// �ʒu�ۑ�(�p�[�c��)
	D3DXVECTOR3 m_aRot[MAX_PLAYER_MODEL];		// �����ۑ�(�p�[�c��)
	D3DXMATRIX	m_mtxWorld;						// ���[���h�}�g���b�N�X
	bool m_bJump;								// �W�����v�����ǂ���
	bool m_bLand;								// ���n�����ǂ���
	float m_fDest;								// �ړI�̊p�x
	float m_fDiff;								// �p�x�̍���

	bool m_bAttack;								// �U�����Ă邩�ǂ���
	bool m_bHit;								// �����������ǂ���
	int	m_nAttackCounter;						// �U���J�E���^�[
	int	m_nJumpCounter;							// �W�����v�J�E���^�[

	CModel * m_apModel[MAX_PLAYER_MODEL];
	D3DXVECTOR3 m_VtxMin, m_VtxMax;				// �ŏ��l�A�ő�l

	KEY_INFO *m_pKeyInfo;						// �L�[���̃|�C���^
	int m_nKey;									// ���݂̃L�[No.
	int m_nCouterMotion;						// ���[�V�����J�E���^�[
	int m_StateSave;							// ��ԕۑ��p
	int m_nNumParts;							// �p�[�c��
	int m_aIndexParent[MAX_PLAYER_MODEL];		// �C���f�b�N�X
	P_KEY m_aKeyOffset[MAX_PLAYER_MODEL];
	MOTION_INFO m_aMotionInfo[NUM_MAX_PLAYER_MOTION];
	char m_aFilenameModel[MAX_PLAYER_MODEL][256];
};
#endif