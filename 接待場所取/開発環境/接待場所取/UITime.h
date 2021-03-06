//=============================================================================
//
// タイム処理 [UITime.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _UITIME_H_
#define _UITIME_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CNumber;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TIME	(3)		// タイムの桁数

//*********************************************************************
//タイムクラスの定義
//*********************************************************************
class CTime : public CScene //派生クラス
{
public:
	CTime(int nPriority = 6);
	~CTime();
	static CTime *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);		//タイム生成
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTime(int nTime);
	void AddTime(int nValue);
	int GetTime();
	void SetColor(D3DXCOLOR col);

private:
	//メンバ変数
	CNumber			*m_apNumber[MAX_TIME];
	D3DXVECTOR3		m_pos;
	float			m_fLength;
	float			m_fWidth, m_fHeight;	// 幅高さ
	int				m_nTime;				// 制限時間
	int				m_nTimerCnt;			// タイマー用カウント
	int				m_nColorFlash;			// 点滅カウント
	int				m_nFadeCnt;				// フェードまでのカウント
};

#endif