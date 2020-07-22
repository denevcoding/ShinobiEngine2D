#pragma once
#ifndef _TIMER_MANAGER_H_
#define _TIMER_MANAGER_H_

//Class to Control the Main Time of the Game
class TimeManager
{
private:
	const double m_fDeltaTime; // Time between every tick process. Seconds.
	double m_fMaxElapsedTime; // Max. elapsed time to process. Seconds.
	
	LARGE_INTEGER m_Frequency; // Freq. of the performance counter.
	LARGE_INTEGER	m_PreviousTime, m_CurrentTime;	// Iteration times.
	
	double	m_fElapsedTime;	// Time between iterations. Storing time remaining from previous process.
	double	m_fTotalTime;	// Total time for every g_fFixedTick since it started. Secs.
	double	m_fTimeBetwSlots;	// Time elpased between 2 Slot calls.
	
public: //Cosntructors DEstructors
	TimeManager(double _fFixedTick);

	// Set/Get Member Variables
	inline void SetMaxElapsedTime(double fElapsedTime) { m_fMaxElapsedTime = fElapsedTime; }
	inline double GetFixedTick() const { return m_fDeltaTime; }
	inline double GetTimeBetwSlots() const { return m_fTimeBetwSlots; }
	inline double GetElapsedTime() const { return m_fElapsedTime; }
	inline double GetTotalTime() const { return m_fTotalTime; }

	//Like On Start Unity
	// To call before Process Slots
	void InitSlotsToProcess();

	//Like Update on Unity
	// Process timer. True if there are next ticks to process
	bool ProcessSlots();
	
};
#endif


