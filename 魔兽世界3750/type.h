#ifndef __TYPE_H__
#define __TYPE_H__
#include <iostream>
#include <memory>
#include <string>

namespace warcraft{
enum Color{RED,BLUE,OTHER};
enum warriorType{DRAGON,NINJA,ICEMAN,LION,WOLF};
using std::string;
inline string toString(Color color){
    switch(color){
    case RED: return "red";
    case BLUE: return "blue";
    case OTHER: return "other";
    default:
                return string();
    }
}
inline string toString(warriorType wtype){
    switch(wtype){
    case DRAGON:return "dragon";
    case NINJA:return "blue";
    case ICEMAN:return "iceman";
    case LION:return "lion";
    case WOLF:return "wolf";
    default:
              return string();
    }
}

class Warrior;
class Headquarters;
class WarriorView;
using std::shared_ptr;
using WarriorPtr=shared_ptr<Warrior>;
using HeadquartersPtr=shared_ptr<Headquarters>;
using WarriorViewPrt=shared_ptr<WarriorView>;
}//end of naspace warcraft
#endif

