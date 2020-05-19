#include "type.h"
#include <vector>
#include <map>
using namespace::std;
namespace warcraft{
class GameConfig
{
public:
    template<typename iter>
        void setOrder(iter beg,iter end){
            while(beg!=end){
                _initWarriorOrder.push_back(*beg);
                ++beg;
            }
        }
    void readFromfile(const string&filename);
    void readFromConsole();
    
    void addGroupId(){++_curGroupId;}
    size_t getCurGroupId(){return _curGroupId;}
    size_t groupsize(){return _groups.size();}

    size_t cityCount(){return _groups[_curGroupId]._Citycount;}
    size_t headQuartersInitElements(){return _groups[_curGroupId]._initElement;}
    size_t warriorInitLife(warriorType wType){
        return _groups[_curGroupId]._warriorLifes[wType];
    }
    size_t warriorInitAttacks(warriorType wType){
        return _groups[_curGroupId]._warriorAttacks[wType];
    }
    
    void show();

    static GameConfig* getInstance(){
        if(_instance==nullptr){
            _instance=new GameConfig();
        }
        return _instance;

    }
    static void destory(){
        if(_instance){
            delete _instance;
        }
    }
private:
    struct BaseData{
        size_t _Citycount;
        size_t _minutes;
        size_t _initElement;
        map<warriorType,size_t> _warriorLifes;
        map<warriorType,size_t> _warriorAttacks;
    };
    void readFromStream(istream&is);
    GameConfig() {cout<<"GameConfig()"<<endl;}
    ~GameConfig() {cout<<"~GameConfig()"<<endl;}
    static GameConfig* _instance;
    
    vector<BaseData> _groups;
    size_t _curGroupId=0;
    vector<warriorType> _initWarriorOrder;
};
}//end of warcraft
