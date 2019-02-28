#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameWorld.h"
class StudentWorld;
class Citizen;
class Penelope;
class Goodie;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject{
public:
    //might not need dir, depth, size
    Actor(int imageID, double x_location, double y_location, Direction dir, int depth, int size, StudentWorld* temp);
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
    //most are default alive
    virtual bool isAlive();
    void setDead();
    virtual ~Actor();
    virtual bool isHuman();
    virtual bool isZombie();
    virtual bool canBeMovedOnto();
    virtual void activateIfAppropiate(Actor* a);
    virtual bool beVomitedOnIfAppropriate();
    virtual void pickUpGoodieIfAppropiate(Goodie* g);
    void setInfectionStatus();
    virtual void dieByFallOrBurnIfAppropriate();
    virtual bool blocksFlame() const;
    //move to agent
    void incrementTickCount();
    int getTickCount();
    bool getInfectionStatus();
private:
    bool infectionStatus;
    int tickCount;
    bool alive;
    StudentWorld* world;
};


//Make class of immovable objects?

class Wall: public Actor{
public:
    Wall(double x_location, double y_location, StudentWorld* temp);
    //walls do something does nothing
    virtual void doSomething();
    virtual bool canBeMovedOnto();
    virtual bool blocksFlame() const;
};
//need to put this under activating object
class ActivatingObject: public Actor{
public:
    ActivatingObject(int imageID, double x_location, double y_location, Direction dir, StudentWorld*temp);
    virtual void doSomething();
};

class Exit: public ActivatingObject{
public:
    Exit(double x_location, double y_location, StudentWorld* temp);
    virtual void doSomething();
    virtual void activateIfAppropiate(Actor* a);
    virtual bool blocksFlame() const;
private:
};


//Destroying stuff section------------------------------


class Flame: public ActivatingObject{
public:
    Flame(double x_location, double y_location, Direction dir, StudentWorld* temp);
    virtual void doSomething();
    void activateIfAppropiate(Actor* temp);
};

class Vomit: public ActivatingObject{
public:
    Vomit(double x_location, double y_location, Direction dir, StudentWorld* temp);
    virtual void doSomething();
    virtual void activateIfAppropiate(Actor*a);
};

class Pit: public ActivatingObject{
public:
    Pit(double x_location, double y_location, StudentWorld* temp);
    virtual void doSomething();
    virtual void activateIfAppropiate(Actor* a);
};

class Landmine:public ActivatingObject{
public:
    virtual void dieByFallOrBurnIfAppropriate();
};

//ALL Agent/DAMAGABLE ITEMS--------------------------------------
class Agent: public Actor{
public:
    Agent(int imageID, double x_location, double y_location, StudentWorld* temp);
    virtual void getDamage();
    virtual bool canBeMovedOnto();
    bool isAgentFreeDirection(double x, double y);
    double appropiateMovementDirection(int change, double distance);
private:
};

//All goodies--------------------------------------------
class Goodie: public ActivatingObject{
public:
    Goodie(int imageID, double x_location, double y_location, StudentWorld* temp);
//    virtual bool canBeMovedOnto();
    virtual void doSomething();
    virtual void giveGoodies(Penelope* p) = 0;
    virtual void activateIfAppropiate(Actor*temp);
    virtual void dieByFallOrBurnIfAppropriate();
};

class VaccineGoodie: public Goodie{
public:
    VaccineGoodie(double x_location, double y_location, StudentWorld* temp);
    virtual void giveGoodies(Penelope* p);
};

class GasCanGoodie: public Goodie{
public:
    GasCanGoodie(double x_location, double y_location, StudentWorld* temp);
    virtual void giveGoodies(Penelope* p);
};

class LandmineGoodie: public Goodie{
public:
    LandmineGoodie(double x_location, double y_location, StudentWorld* temp);
    virtual void giveGoodies(Penelope* p);
};


//HUMANS------------------------------------------------
class Human: public Agent{
public:
    Human(int imageID, double x_location, double y_location, StudentWorld* temp);
    virtual bool isHuman();
    virtual bool beVomitedOnIfAppropriate();
    void incrementInfectionCount();
    int getInfectionCount();
    void doSomething();
    virtual void doDifferentHumanStuff() = 0;
private:
    int infectionCount;
};
//CITIZEN
class Citizen: public Human{
public:
    Citizen(double x_location, double y_location, StudentWorld* temp);
    virtual void doSomething();
    virtual void doDifferentHumanStuff();
    virtual void dieByFallOrBurnIfAppropriate();
private:
};
//PENELOPE
class Penelope: public Human{   
public:
    Penelope(double x_location, double y_location, StudentWorld* temp);
    virtual void doSomething();
    virtual bool isHuman();
    virtual void doDifferentHumanStuff();
    void incrementVaccines(int amt);
    void incrementLandmines(int amt);
    void incrementFlameCharges(int amt);
    int getFlameCharges();
    int getVaccines();
    int getLandmines();
    virtual void pickUpGoodieIfAppropiate(Goodie* g);
    virtual void dieByFallOrBurnIfAppropriate();
private:
    int createFlames();
    int flamethrowerCount;
    int vaccines;
    int landmines;
};

//ZOMBIES--------------------
class Zombie: public Agent{
public:
    Zombie(double x_location, double y_location, StudentWorld* temp);
    virtual bool isZombie();
    virtual void doSomething();
    int getMovementPlan();
    void setMovementPlan(int plan);
    bool addVomitIfAppropiate(double vomit_x, double vomit_y);
    virtual void doDifferentZombieStuff() = 0;
    
private:
    int movementPlan;
};

class SmartZombie: public Zombie{
public:
    SmartZombie(double x_location, double y_location, StudentWorld* temp);
    virtual void doSomething();
    virtual void doDifferentZombieStuff();
    virtual void dieByFallOrBurnIfAppropriate();
};

class DumbZombie: public Zombie{
public:
    DumbZombie(double x_location, double y_location, StudentWorld* temp);
    virtual void doSomething();
    virtual void doDifferentZombieStuff();
    virtual void dieByFallOrBurnIfAppropriate();
};
#endif // ACTOR_H_
