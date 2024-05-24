#pragma once
#include"../GameLib/game_lib.h"
#include"../GameLib/obj2d_data.h"
#include"actor.h"


class BasePlayerBehavior : public ActorBehavior
{
private:
    void init(std::shared_ptr<OBJ2D> obj) const override;
    void moveX(std::shared_ptr<OBJ2D> obj) const;
    OBJ_TYPE getType() const override { return OBJ_TYPE::PLAYER; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ENEMY; }
    void hitrect(std::shared_ptr<OBJ2D> src, std::shared_ptr<OBJ2D> dst) const override;
    void counter(std::shared_ptr<OBJ2D> obj)const override;
    bool isAlive(std::shared_ptr<OBJ2D> obj) const;
    void damageProc(std::shared_ptr<OBJ2D> obj) const override;

};

class WalkPlayerBehavior : public BasePlayerBehavior
{
public:
    WalkPlayerBehavior();
private:
    void moveY(std::shared_ptr<OBJ2D> obj) const override;
    void jump(std::shared_ptr<OBJ2D> obj) const override;
    void attack(std::shared_ptr<OBJ2D> obj) const override {}
  //  void dash(std::shared_ptr<OBJ2D>obj)const override;
};
extern std::shared_ptr<WalkPlayerBehavior>walkPlayerBehavior;

