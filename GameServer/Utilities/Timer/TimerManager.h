#ifndef _UTILITIES_TIMER_MANAGER_H_
#define _UTILITIES_TIMER_MANAGER_H_

#include <vector>
#include "Timer.h"

namespace Utilities {

class TimerManager
{
public:
	TimerManager();
	~TimerManager();

	/* Update the timer's elapsed time */
	void Tick();

	/* Add a new timer */
	void AddTimer(Timer* timer);

private:
	/* Get the tick time(Marcosecons) */
	time_t TickTime();

	/* Clear all timers */
	void Clear();

private:
	std::vector<Timer*> m_timers;
	time_t m_last_ttime;
};

}; // namespace Utilities

#endif // _UTILITIES_TIMER_MANAGER_H_