#ifndef WINDOW_H
#define WINDOW_H
#include"controller\controller.h"

class Window :public NetReceiver
{
public:
     Window();

     virtual void recv(json content);

    virtual void disconnect(status status)=0;

};

#endif // WINDOW_H
