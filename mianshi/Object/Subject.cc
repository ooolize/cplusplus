#include "Subject.h"
void Ring::attach(Object* obj){
    auto iter=std::find(_objs.begin(),_objs.end(),obj);
    if(iter==_objs.end()){
        _objs.push_back(obj);
    }
}
void Ring::detach(Object* obj){
    auto iter=std::find(_objs.begin(),_objs.end(),obj);
    if(iter!=_objs.end()){
        _objs.erase(iter);
    }
}
void Ring::notify(){
    for(auto &p:_objs){
        p->update();
    }
}
void Ring::press(){
    if(!_isRinging){
        _isRinging=true;
        notify();
    }
    _isRinging=false;
}

