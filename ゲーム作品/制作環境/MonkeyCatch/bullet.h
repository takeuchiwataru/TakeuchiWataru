//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : �|���j
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "billboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULEET_TEXTURE_000 "data/TEXTURE/bullet000.png"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CBullet : public CBillBoard
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:
	CBullet();
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CBullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// ���L�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_pos;			// �ʒu
	D3DXVECTOR3				m_move;			// �ړ���
	int						m_nLife;
};
#endif