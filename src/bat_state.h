#ifndef BAT_STATE_H_
#define BAT_STATE_H_

class Bat;

class BatState {
  public:
    virtual ~BatState() {}
    virtual void Initialize(Bat& bat) = 0;
    virtual void Update(float seconds_elapsed, Bat& bat) = 0;
};

#endif // BAT_STATE_H_
