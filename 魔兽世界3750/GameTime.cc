#include "GameTime.h"
#include <iomanip>
namespace warcraft{
GameTime* GameTime::_instance=getInstance();
pthread_once_t GameTime::_once=PTHREAD_ONCE_INIT;

GameTime* GameTime::getInstance(){
        pthread_once(&_once,init);
        return _instance;
}
void GameTime::init(){
        if(_instance==nullptr){
            _instance=new GameTime();
        }
        ::atexit(destory);
}
void GameTime::updata(){
    _mins+=10;
    if(_mins>=60){
        _hours++;
        _mins=0;
    }
}

void GameTime::showTime(){
    cout<<setw(2)<<_hours<<":"
        <<setw(2)<<_mins;
}
}
