#pragma once

#ifndef __XSOUND__
#define __XSOUND__

#include<xact3.h>

enum EWaveName {WAVENAME_CAR_IMPACT_DASH, WAVENAME_CAR_IMPACT_GLASS1, WAVENAME_CAR_IMPACT_GLASS2, WAVENAME_MENU_SCROLL_BLIP, WAVENAME_CAR_SKID1, WAVENAME_CAR_SKID2, WAVENAME_CAR_ENGINE_IDLE};

const float		MAX_PITCH_LEVEL =  1800;
const float		MIN_PITCH_LEVEL = -1000;

class XSound
{
	static XSound			*ms_pXSound;
	IXACT3Engine			*m_pXactEngine;
	IXACT3WaveBank			*m_pWaveBank;
	IXACT3SoundBank			*m_pSoundBank;
	IXACT3Wave				*m_outWave;

	EWaveName				m_eWaveName;

	BOOL					m_isDone;

	XSound(void);
public:
	static XSound*			GetInstance();
	~XSound(void);

	void					Destroy();
	void					Update();
	void				    LoadWaveBank();
	void					LoadSoundBank();
	void					PlayWave(EWaveName _eWaveName, short _pitchLevel,BOOL _stopPrevious);
	void					PlayWaveSimple(EWaveName _eWaveName);
	void					PlaySound( short _pitchLevel);
	float					GetDuration();
};

#endif