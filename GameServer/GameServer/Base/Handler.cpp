#include "Handler.h"

Handler::Handler(StdLog* log)
: SocketHandler(log)
{
}

Handler::Handler(IMutex& mutex, StdLog* log)
: SocketHandler(mutex, log)
{
}

Handler::Handler(IMutex& mutex, ISocketHandler& parent, StdLog* log)
: SocketHandler(mutex, parent, log)
{
}
