//=============================================================================
//
// 敵処理 [enemy.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// 前方宣言 インクルードはいらない
//*****************************************************************************
class CObject;
class CPlayer;
class CRemain;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_MOVE_SPEED (2.0f)
#define MAX_ENEMY_MODEL (10)			// 敵のパーツ数
#define NUM_MAX_ENEMY_KEY (2)			// キー最大数
#define NUM_MAX_ENEMY_MOTION (3)		// モーション最大数
#define ENEMY_RADIUS (10)
#define ENEMY_MAX_POS (1490)
#define ENEMY_MIN_POS (0)
#define NUM_ENEMY (10)					// 敵の総数
#define E_MAX_PARTICLE (20)				// パーティクル数
#define E_PARTICLE_LIFE (30)			// パーティクルライフ
#define E_PARTICLE_RADIUS (30)			// パーティクルの大きさ
#define ENEMY_COLLISION (2000.0f)		// 敵の当たり判定の半径

#define ENEMY_FILE ("data/TEXT/motion_enemy.txt")
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
// クラスの定義
//*****************************************************************************
class CEnemy : public CScene
{
public:
	typedef struct
	{// キー設定
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}E_KEY;

	typedef struct
	{// キー情報
		int nFrame;
		E_KEY aKey[MAX_ENEMY_MODEL];
	}KEY_INFO;

	typedef struct
	{// モーション情報
		bool bLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[NUM_MAX_ENEMY_KEY];
	}MOTION_INFO;

	typedef enum
	{// 敵の状態
		ENEMYSTATE_NONE = 0,
		ENEMYSTATE_NORMAL,		// 通常
		ENEMYSTATE_MOVE,		// 移動
		ENEMYSTATE_MAX
	}ENEMYSTATE;

	typedef enum
	{// 敵の種類
		ENEMYTYPE_000,			// 動かない
		ENEMYTYPE_001,			// ランダム
		ENEMYTYPE_002,			// 横
		ENEMYTYPE_003,			// 縦
		ENEMYTYPE_004,			// 横 ver2
		ENEMYTYPE_005,			// 縦 ver2
		ENEMYTYPE_MAX
	}ENEMYTYPE;

	CEnemy();
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void UpdateTutorial(void);
	void Draw(void);
	void LoadMotion(void);
	void UpdateMotion(void);
	char *ReadLine(FILE * pFile, char *pDst);
	char *GetLineTop(char *pSrc);
	int PopString(char * pSrc, char * pDst);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMax, D3DXVECTOR3 *pVtxMin);
	void SetType(ENEMYTYPE type);

	// 静的メンバ関数
	static CEnemy * Create(D3DXVECTOR3 pos, ENEMYTYPE type);
	static int GetNumEnemy(void);
	static int GetCatchEnemy(void);

	// 静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;	// 共有テクスチャのポインタ
	static LPD3DXMESH		m_apMesh[MAX_ENEMY_MODEL];				// メッシュ情報へのポインタ
	static LPD3DXBUFFER		m_apBuffMat[MAX_ENEMY_MODEL];			// マテリアル情報へのポインタ
	static DWORD			m_anNumMat[MAX_ENEMY_MODEL];			// マテリアル情報の数
	static int m_nNumEnemy;											// 敵の総数
	static int m_nGetEnemy;											// ゲットした敵の数
	static CMeshOrbit * m_pMeshOrbit;
	static CObject * m_pObject;
	static CPlayer *m_pPlayer;

private:
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_posold;						// 位置
	D3DXVECTOR3 m_move;							// 移動
	D3DXVECTOR3 m_rot;							// 向き
	ENEMYSTATE m_state;							// 状態
	D3DXVECTOR3	m_aPosOffset[MAX_ENEMY_MODEL];	// モデルのオフセット
	D3DXMATRIX	m_mtxWorld;						// ワールドマトリックス
	bool m_bJump;								// ジャンプするかしないか
	bool m_bDisp;								// 表示するかどうか
	float m_fRadius;							// 半径
	float m_fDest;								// 目的の角度
	float m_fDiff;								// 角度の差分

	CModel * m_apModel[MAX_ENEMY_MODEL];
	D3DXVECTOR3 m_VtxMin, m_VtxMax;				// 最小値、最大値

	KEY_INFO *m_pKeyInfo;					// キー情報のポインタ
	int m_nKey;								// 現在のキーNo.
	int m_nCouterMotion;					// モーションカウンター
	int m_StateSave;						// 状態保存用
	int m_nNumParts;						// パーツ数
	int m_aIndexParent[MAX_ENEMY_MODEL];	// インデックス
	E_KEY m_aKeyOffset[MAX_ENEMY_MODEL];
	MOTION_INFO m_aMotionInfo[NUM_MAX_ENEMY_MOTION];
	char m_aFilenameModel[MAX_ENEMY_MODEL][256];

	bool m_bUse;
	bool m_bHit;							// 当たったかどうか
	bool m_bHitGrass;						// 草に当たったかどうか
	bool m_bHitObject;						// オブジェクトに当たったかどうか
	ENEMYTYPE m_type;						// 敵の種類
	int m_MoveCounter;						// 移動カウンター
};
#endif