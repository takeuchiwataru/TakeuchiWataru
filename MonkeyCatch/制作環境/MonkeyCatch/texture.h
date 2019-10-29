//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : �|���j
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXTURE (14)

#define FRAME_TEXTURE000 "data/TEXTURE/timer_frame2.png"		// �^�C�}�[�t���[��
#define FRAME_TEXTURE001 "data/TEXTURE/score_frame.png"			// �X�R�A�t���[��
#define IMAGE_TEXTURE000 "data/TEXTURE/remain.png"				// �T���̃J�E���g�摜
#define IMAGE_TEXTURE001 "data/TEXTURE/UI000.png"				// �c��
#define IMAGE_TEXTURE002 "data/TEXTURE/tutorial000.png"			// �R���g���[���[����
#define IMAGE_TEXTURE003 "data/TEXTURE/UI001.png"				// �߂܂�����
#define IMAGE_TEXTURE004 "data/TEXTURE/UI002.png"				// �c�莞��
#define IMAGE_TEXTURE005 "data/TEXTURE/UI003.png"				// ���v
#define PARTICLE_TEXTURE_000 "data/TEXTURE/effect000.jpg"		// �G�t�F�N�g�̃e�N�X�`��
#define PARTICLE_TEXTURE_001 "data/TEXTURE/effect000.jpg"		// �G�t�F�N�g�̃e�N�X�`��
#define PAUSEMAT_TEXTURE	"data/TEXTURE/pause100.png"			// �|�[�Y�䎆�̃e�N�X�`��
#define PAUSESELECT_TEXTURE000	"data/TEXTURE/pause000.png"		// CONTINUE
#define PAUSESELECT_TEXTURE001	"data/TEXTURE/pause001.png"		// RETRY
#define PAUSESELECT_TEXTURE002	"data/TEXTURE/pause002.png"		// QUIT

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CTexture
{
public:
	CTexture();
	~CTexture();
	static HRESULT Load(void);
	static void Unload(void);
	static LPDIRECT3DTEXTURE9 GetTexture(int nIdx);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];		// �z��ver
	//static LPDIRECT3DTEXTURE9 m_pTexture;					// ���I�m��ver

	static const char *m_apFileName[];

};

#endif