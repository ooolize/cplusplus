#include "type.h"
#include "GameConfig.h"
#include "GameTime.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace warcraft;
void test0(){
    vector<warriorType> blue{
        DRAGON,
            NINJA,
            ICEMAN,
            LION,
            WOLF
    };
    vector<warriorType> red{
        ICEMAN, 
            LION, 
            WOLF,
            NINJA, 
            DRAGON, 
    };

    vector<warriorType> readOread{
            LION, 
            DRAGON, 
            NINJA, 
            ICEMAN, 
            WOLF
    };
    GameConfig::getInstance()->setOrder(readOread.begin(),readOread.end());
    GameConfig::getInstance()->readFromfile("warcraft.conf");   
    GameConfig::getInstance()->show();
#if 1
    for(int i=0;i<10;++i){
        GameTime::getInstance()->updata();
        GameTime::getInstance()->showTime();
        cout<<endl;
    }
#endif
}

int main()
{
    test0();
    return 0;
}

