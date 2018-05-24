#ifndef ZOMBIE_STATE_H_
#define ZOMBIE_STATE_H_

class Zombie;

class ZombieState {
  public:
    virtual ~ZombieState() {}
    virtual void Initialize(Zombie& zombie) = 0;
    virtual void Update(float seconds_elapsed, Zombie& zombie) = 0;
};

#endif // ZOMEBIE_STATE_H_

