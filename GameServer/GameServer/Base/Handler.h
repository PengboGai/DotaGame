#ifndef _BASE_HANDLER_H_
#define _BASE_HANDLER_H_

#include "SocketHandler.h"

class Handler : public SocketHandler
{
public:
    Handler(StdLog* log = NULL);
    Handler(IMutex& mutex, StdLog* log = NULL);
    Handler(IMutex& mutex, ISocketHandler& parent, StdLog* log = NULL);
};

#endif // _BASE_HANDLER_H_