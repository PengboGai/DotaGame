#ifndef _UTILITIES_DEBUG_H_
#define _UTILITIES_DEBUG_H_

namespace Utilities {

class Debug
{
protected:
	Debug();
	~Debug();

public:
	static void Log(const char* format, ...);
};

}; // namespace Utilities

#endif // _UTILITIES_DEBUG_H_