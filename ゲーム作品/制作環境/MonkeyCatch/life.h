//=============================================================================
//
// ���C�t���� [life.h]
// Author : �|���j
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIFE (3)				// �ő僉�C�t��
#define LIFE_INTERVAL_SIZE (45)		// ���C�t�Ԋu

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CLife : public CScene
{
public:
	CLife();
	~CLife();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddLife(int nValue);

	// �ÓI�����o�֐�
	static CLife * Create(D3DXVECTOR3 pos);

private:
	static CPolygon * m_apPolygon[MAX_LIFE];
	int m_nLife;
};

#endif