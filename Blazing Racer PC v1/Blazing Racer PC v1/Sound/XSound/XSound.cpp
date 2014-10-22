#include "stdafx.h"
#include "XSound.h"

#ifdef XBOX
#include "AtgUtil.h"
using namespace ATG;
#endif

XSound* XSound::ms_pXSound = nullptr;

XSound::XSound(void)
{
		XACT_RUNTIME_PARAMETERS EngineParameters = { 0 };

		XACT3CreateEngine(0, &m_pXactEngine);
		m_pXactEngine->Initialize(&EngineParameters);
		m_isDone = FALSE;
		m_outWave = nullptr;
}

XSound::~XSound(void)
{
}

void XSound::Destroy()
{

}

XSound* XSound::GetInstance()
{
	if(ms_pXSound == nullptr)
		ms_pXSound = new XSound();
	return ms_pXSound;
}

void XSound::Update()
{
	m_pXactEngine->DoWork();
}

void XSound::LoadWaveBank()
{
	LPCSTR str;
	DWORD dwFileSize = 0;

	VOID* pbWaveBank = NULL;
	
#ifdef XBOX
	ATG::LoadFilePhysicalMemory("Game:\\Content\\Sound\\WaveData.xwb", &pbWaveBank, &dwFileSize);
#else
		str = "Content\\Sound\\WaveData.xwb";
		HANDLE hFile = CreateFile(str, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != -1)
		{
			//pbWaveBank = new BYTE[dwFileSize];
			HANDLE  hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL);
			if (hMapFile)
			{
				pbWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
				//DWORD dwBytesRead;
				//ReadFile(hFile, pbWaveBank, dwFileSize,0, NULL);
			}
		}
		CloseHandle(hFile);
	
#endif
		if (pbWaveBank)
		{
			if (FAILED(m_pXactEngine->CreateInMemoryWaveBank(pbWaveBank, dwFileSize, 0, 0, &m_pWaveBank)))
				OutputDebugString("failed");
		}
}

void XSound::LoadSoundBank()
{
	LPCSTR str;
	DWORD dwFileSize = 0;

	VOID* pbSoundBank = NULL;
#ifdef XBOX
	ATG::LoadFilePhysicalMemory("Game:\\Content\\Sound\\WaveData.xwb", &pbSoundBank, &dwFileSize);
#else
		str = "Content\\Sound\\WaveData.xwb";
		HANDLE hFile = CreateFile(str, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != -1)
		{
			pbSoundBank = new BYTE[dwFileSize];
			DWORD dwBytesRead;
			ReadFile(hFile, pbSoundBank, dwFileSize, &dwBytesRead, NULL);
		}
		CloseHandle(hFile);
#endif
	if (pbSoundBank)
		m_pXactEngine->CreateInMemoryWaveBank(pbSoundBank, dwFileSize, 0, 0, &m_pWaveBank);
}

void XSound::PlayWave(EWaveName _eWaveName, short _pitchLevel, BOOL _stopPrevious)
{/*
	DWORD PlayingState = 0;

	XACTPITCH pitch = _pitchLevel;

	if(_stopPrevious)
	{
		DWORD value = 0;
		//if(m_outWave != nullptr)
		m_outWave->Stop(value);
		m_isDone = FALSE;
	}

	if(!m_isDone)
	{
		m_pWaveBank->Prepare(_eWaveName, 0, 0, 1, &m_outWave);
		m_outWave->SetPitch(pitch);
		m_outWave->Play();
		m_isDone = TRUE;
	}

	m_outWave->GetState(&PlayingState);

	if(PlayingState == XACT_STATE_STOPPED)
		m_isDone = FALSE;*/
}

void XSound::PlayWaveSimple(EWaveName _waveName)
{
	/*DWORD PlayingState = 0;

	if(!m_isDone)
	{
		m_pWaveBank->Play(_waveName , 0, 0, 1, &m_outWave);
		m_isDone = TRUE;
	}

	m_outWave->GetState(&PlayingState);

	if(PlayingState == XACT_STATE_STOPPED)
		m_isDone = FALSE;
*/
}

void XSound::PlaySound(short _pitchLevel)
{

}

float XSound::GetDuration()
{
	XACT_WAVE_PROPERTIES prop = { 0 };
	m_pWaveBank->GetWaveProperties(0, &prop);

	DWORD duration = prop.durationInSamples;
	return duration;
}