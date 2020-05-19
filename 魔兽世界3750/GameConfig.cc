#include "GameConfig.h"
#include <fstream>
#include <sstream>
namespace warcraft{
GameConfig* GameConfig::_instance=getInstance();

void GameConfig::readFromfile(const string&filename){
    ifstream ifs(filename);
    if(!ifs){
        cout<<"open file "<<filename<<"error!"<<endl;
        return;
    }
    readFromStream(ifs);
    ifs.close();
}
void GameConfig::readFromConsole(){
    cout<<"please enter data in order"<<endl;
    readFromStream(cin);
}
void GameConfig::readFromStream(istream& is){
    string line;
    int groupNum;
    getline(is,line);
    {
    istringstream iss(line);
    iss>>groupNum;    
    }
    for(int i=0;i<groupNum;i++){
        BaseData tmpData;
        //data line 1
        getline(is,line);
        {
            istringstream iss(line);
            iss>>tmpData._initElement;
            iss>>tmpData._Citycount;
            iss>>tmpData._minutes;
        }
        //data line 2
        getline(is,line);
        {
            istringstream iss(line);
            int value,idx=0;
            while(iss>>value)
                tmpData._warriorLifes.insert
                    (std::make_pair(_initWarriorOrder[idx++],value));
        }
        //data line 3
        getline(is, line);
        {
            istringstream iss(line);
            int value,idx=0;
            while(iss>>value)
                tmpData._warriorAttacks.insert
                    (std::make_pair(_initWarriorOrder[idx++],value));
        }
        _groups.push_back(std::move(tmpData));
    }
}
void GameConfig::show(){
    for(auto &p:_groups){
        cout<<"_initElement = "<<p._initElement<<endl
            <<"_Citycount = "<<p._Citycount<<endl
            <<"_minutes = "<<p._minutes<<endl;
        for(auto q:p._warriorLifes){
            cout<<q.second<<" ";
        }
        cout<<endl;
        for(auto q:p._warriorAttacks){
            cout<<q.second<<" ";
        }
        cout<<endl;
    }
}

}
