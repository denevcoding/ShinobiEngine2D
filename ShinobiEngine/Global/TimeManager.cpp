#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager(double l_fDeltaTime) :

  m_fDeltaTime(l_fDeltaTime)
, m_fElapsedTime(0.0f)
, m_fMaxElapsedTime(1.0f / 10.0f)
, m_fTimeBetwSlots(0.0f)
, m_fTotalTime(0.0f)

{
	QueryPerformanceFrequency(&m_Frequency);	// Freq. cached.
	QueryPerformanceCounter(&m_PreviousTime);	// Init. prev. time.
	QueryPerformanceCounter(&m_CurrentTime);
}


void TimeManager::InitSlotsToProcess()
{
	QueryPerformanceCounter(&m_CurrentTime);
	LARGE_INTEGER elapsed;
	elapsed.QuadPart = m_CurrentTime.QuadPart - m_PreviousTime.QuadPart;
	m_PreviousTime = m_CurrentTime;
	// Adding time elapsed from previous process to remaing time.
	m_fTimeBetwSlots = static_cast<double>(elapsed.QuadPart) / static_cast<double>(m_Frequency.QuadPart);
	m_fElapsedTime += m_fTimeBetwSlots;

	//to fix number of iterations
	if (m_fElapsedTime > m_fMaxElapsedTime)
	{
		m_fElapsedTime = m_fMaxElapsedTime;
	}
}


bool TimeManager::ProcessSlots()
{
	if (m_fElapsedTime >= m_fDeltaTime)
	{
		m_fTotalTime += m_fDeltaTime;	// Secs.
		m_fElapsedTime -= m_fDeltaTime;
		return true;
	}
	return false;
}