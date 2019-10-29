//=============================================================================
//
// �e�N�X�`������ [textue.cpp]
// Author : �|���j
//
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[MAX_TEXTURE] = {};
//LPDIRECT3DTEXTURE9 CTexture::m_pTexture = NULL;

const char * CTexture::m_apFileName[] =
{// �e�N�X�`���̃t�@�C����
	FRAME_TEXTURE000,		// �^�C�}�[�t���[��		(0)
	FRAME_TEXTURE001,		// �X�R�A�t���[��		(1)
	IMAGE_TEXTURE000,		// �T���̃J�E���g�摜	(2)
	IMAGE_TEXTURE001,		// �c��摜				(3)
	IMAGE_TEXTURE002,		// �R���g���[���[�̐���	(4)
	IMAGE_TEXTURE003,		// �߂܂������摜		(5)
	IMAGE_TEXTURE004,		// �c��摜				(6)
	IMAGE_TEXTURE005,		// ���v�摜				(7)
	PARTICLE_TEXTURE_000,	// �G�t�F�N�g			(8)
	PARTICLE_TEXTURE_001,	// �G�t�F�N�g			(9)
	PAUSEMAT_TEXTURE,		// �|�[�Y�䎆			(10)
	PAUSESELECT_TEXTURE000,	// CONTINUE				(11)
	PAUSESELECT_TEXTURE001,	// RETRY				(12)
	PAUSESELECT_TEXTURE002,	// QUIT					(13)
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CTexture::Load(void)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();


	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		//// �e�N�X�`���̐���(���I�m��ver)
		//D3DXCreateTextureFromFile(pDevice, m_apFileName[nCntTex],&m_pTexture);

		// �e�N�X�`���̐���(�z��ver)
		D3DXCreateTextureFromFile(pDevice, m_apFileName[nCntTex], &m_apTexture[nCntTex]);
	}

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CTexture::Unload(void)
{
	//// �e�N�X�`���̔j��
	//if (m_pTexture != NULL)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = NULL;
	//}

	//// �������̊J��
	//delete m_pTexture;

	//// NULL�ɂ���
	//m_pTexture = NULL;


	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
//=============================================================================
// �e�N�X�`���̎擾
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(int nIdx)
{
	return m_apTexture[nIdx];
}
////=============================================================================
//// �e�N�X�`���̎擾
////=============================================================================
//LPDIRECT3DTEXTURE9 CTexture::GetTexture(int nIdx)
//{
//	return m_pTexture;
//}
