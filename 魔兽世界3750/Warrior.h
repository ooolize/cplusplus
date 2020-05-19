#ifndef __WARRIOR_H__
#define __WARRIOR_H__
#include "type.h"
namespace  warcraft{

class Headquarters;
class Warrior
{
public:
    Warrior(Color color,string name,size_t id
            ,size_t hp,size_t force,warriorType type)
    :_color(color)
    ,_name(name)
    ,_id(id)
    ,_hp(hp)
    ,_force(force)
    ,_type(type)
    {

    }
    virtual ~Warrior(){}

    size_t getHp(){return  _hp;}
    size_t getColor(){return _color;}
    string getName(){return _name;}
    size_t getCityId(){return _city_id;}
    size_t getEarnElement(){return _earnElements;}
    size_t getForce(){return _force;}
    warriorType getType(){return _type;}

    void setCity(size_t cityNum){_city_id=cityNum;}
    void setElement(size_t earnElements){_earnElements=earnElements;}
    void setHp(size_t hp){_hp=hp;}
    void setHeadquarters(Headquarters*headquarters){_headquarters=headquarters;}

    virtual double getMorale(){return 0;}
    virtual size_t getLoyalty(){return 0;}
    virtual void march();
    virtual void attack(WarriorPtr);
    virtual void defense(WarriorPtr);
    void bewinner();
    void bereward();
private:
    Color _color;
    string _name;
    size_t _id;
    size_t _hp;
    size_t _city_id;
    size_t _force;
    size_t _earnElements;
    warriorType _type;
    Headquarters* _headquarters;
};

class Dragon
:public Warrior
{
public:
    Dragon(Color color,size_t id
            ,size_t hp,size_t force,size_t morale)
    :Warrior(color,"dragon",id,hp,force,DRAGON)
    ,_morale(morale)
    {
    
    }
    double getMorale()override{return _morale;}
private:
    double _morale;
};


class Ninja
:public Warrior
{
public:
    Ninja(Color color,size_t id
            ,size_t hp,size_t force)
    :Warrior(color,"Ninja",id,hp,force,NINJA)
    {

    }
    virtual
    void defense(WarriorPtr warrior)override;
};

class Iceman
:public Warrior
{
    Iceman(Color color,size_t id
            ,size_t hp,size_t force)
    :Warrior(color,"Iceman",id,hp,force,ICEMAN)
    {
        
    }   
    void march()override;
private:
    size_t _setps;
};

class Lion
:public Warrior
{
    Lion(Color color,size_t id
            ,size_t hp,size_t force)
    :Warrior(color,"Lion",id,hp,force,LION)
    {
           
    }
    size_t getLoyalty(){return _loyalty;}
private:
    size_t _loyalty;
};

class Wolf
:public Warrior
{
    Wolf(Color color,size_t id
            ,size_t hp,size_t force)
    :Warrior(color,"Wolf",id,hp,force,WOLF)
    {
           
    }
    void attack(WarriorPtr warrior)override;
private:
    size_t killNums;
    
};

/* ````````````````view`````````````````` */
class WarriorView{
public:
    WarriorView(WarriorPtr warrior)
    :_warrior(warrior)
    {}
    virtual ~WarriorView(){}

    void showBorn()const;
    void showMarch()const;
    void showEarnElements() const;
    void showName() const;
    void showToCity() const;
    void showInCity() const;
    void showDeath() const;
    void showElementsAndForces() const;
protected:
    WarriorPtr _warrior;
};

class DragonView
:public WarriorView
{
    DragonView(WarriorPtr warror)
    :WarriorView(warror)
    {

    }
    void showYell()const;
};
class NinjaView
: public WarriorView
{
public:
        NinjaView(WarriorPtr warrior)
        : WarriorView(warrior)
        {}
};

class IcemanView
: public WarriorView
{
public:
    IcemanView(WarriorPtr warrior)
        : WarriorView(warrior)
    {}

};

class LionView 
: public WarriorView
{
public:
    LionView(WarriorPtr warrior)
        : WarriorView(warrior)
    {}

};

class WolfView
: public WarriorView
{
public:
    WolfView(WarriorPtr warrior)
        : WarriorView(warrior)
    {}
};
class BattleView
{
    BattleView(Warrior& warrior1,Warrior&warrior2)
    :_warrior1(warrior1)
    ,_warrior2(warrior2)
    {

    }
    void showbattle()const;
private:
    Warrior _warrior1;
    Warrior _warrior2;
};
}//end of namespace
#endif
