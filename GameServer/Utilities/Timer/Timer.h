#ifndef _UTILITIES_TIMER_H_
#define _UTILITIES_TIMER_H_

#include <functional>
#include <time.h>

namespace Utilities {

typedef std::function<void(time_t dt)> TIMER_CALLBACK;

class Timer
{
public:
	const static int REPEAT_FOREVER = -1;
	const static int NO_REPEAT = 1;

public:
	/** Timer constructor
		\param callback Timer callback
		\param interval Callback interval (Milliseconds)
		\param repeat Repeat time */
	Timer(TIMER_CALLBACK callback, time_t interval);
	Timer(TIMER_CALLBACK callback, time_t interval, int repeat);
	~Timer();

public:
	/* Update the timer tick, return false if the time is expired 
		\param dt Time delay (Millisecons) */
	bool Update(time_t dt);

private:
	time_t m_interval;
	time_t m_elapsed;
	int m_repeat;
	TIMER_CALLBACK m_callback;
};

}; // namespace Utilities

#endif // _UTILITIES_TIMER_H_