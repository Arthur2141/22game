#pragma once
#pragma once
#include"obj2d.h"
class ActorBehavior : public Behavior
{
protected:
    struct Param
    {
        // アニメーション
        GameLib::AnimeData* ANIME_UP_RIGHT = nullptr;
        GameLib::AnimeData* ANIME_UP_LEFT = nullptr;

        GameLib::AnimeData* ANIME_IDLE_LEFT = nullptr;
        GameLib::AnimeData* ANIME_IDLE_RIGHT = nullptr;

        GameLib::AnimeData* ANIME_COUNTER_RIGHT = nullptr;
        GameLib::AnimeData* ANIME_COUNTER_LEFT = nullptr;

        GameLib::AnimeData* ANIME_RIGHT = nullptr;
        GameLib::AnimeData* ANIME_LEFT = nullptr;

        // サイズ
        VECTOR2 SIZE = { 0, 0 };
        VECTOR2 SCALE = { 1, 1 };
        GameLib::fRECT HIT_BOX = {};
        GameLib::fRECT ATTACK_BOX = {};

        int HP = 1;
        int ATTACK_POWER = 1;

        // 速度関連のパラメータ
        float ACCEL_X = 0.0f;
        float ACCEL_Y = 0.0f;
        float SPEED_X_MAX = 0.0f;
        float SPEED_Y_MAX = 0.0f;
        float JUMP_POWER_Y = 0.0f;
        float DUSH_POWER = 0.0f;
    } param_;
    const Param* getParam() const { return &param_; }

    virtual void moveY(std::shared_ptr<OBJ2D> obj) const;
    virtual void moveX(std::shared_ptr<OBJ2D> obj) const;

protected:
    void move(std::shared_ptr<OBJ2D> obj) const override;

    virtual void init(std::shared_ptr<OBJ2D>obj) const {};
    virtual void jump(std::shared_ptr<OBJ2D>obj) const {};
    virtual void dash(std::shared_ptr<OBJ2D>obj) const {};
    virtual void counter(std::shared_ptr<OBJ2D>obj) const {};
   
    void areaCheck(std::shared_ptr<OBJ2D> obj) const;
    virtual void turn(std::shared_ptr<OBJ2D>) const {}
    virtual void attack(std::shared_ptr<OBJ2D>) const {}

    virtual bool isAlive(std::shared_ptr<OBJ2D>) const = 0;
    virtual void damageProc(std::shared_ptr<OBJ2D>) const {}  // ダメージ処理
};