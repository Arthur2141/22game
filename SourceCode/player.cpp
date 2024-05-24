#include"actor.h"
#include"player.h"
#include"sprite_data.h"
#include"../GameLib/obj2d_data.h"
#include "game.h"


namespace
{   // ※このデータは長いので、Visual Studioの機能で閉じられるようにnamespaceを分けている

    
}

std::shared_ptr<WalkPlayerBehavior>walkPlayerBehavior;

void BasePlayerBehavior::init(std::shared_ptr<OBJ2D> obj) const
{
    
    obj->getComponent<Collider>()->judgeFlag_ = true;
    obj->getComponent<Collider>()->isDrawHitRect_ = true;
    obj->getComponent<Collider>()->isDrawAttackRect_ = true;
    obj->getComponent<Collider>()->radius_ = 0;
    obj->getComponent<Renderer>()->Texsize_ = { 700,700 };
    obj->transform_->scale_ = { 0.5f,0.5f };
    obj->getComponent<ActorComponent>()->hp_ = 3;
}

void BasePlayerBehavior::moveX(std::shared_ptr<OBJ2D> obj) const
{
 
    switch (obj->getComponent<ActorComponent>()->padState_ & (GameLib::input::PAD_LEFT | GameLib::input::PAD_RIGHT))
    {
    case GameLib::input::PAD_LEFT:  // 左だけが押されている場合
        obj->transform_->velocity_.x -= getParam()->ACCEL_X;
        obj->getComponent<ActorComponent>()->xFlip_ = true;
        if (obj->getComponent<ActorComponent>()->onGround_)
        {
        obj->getComponent<Renderer>()->animeData_ = getParam()->ANIME_LEFT;
        }
        break;
    case GameLib::input::PAD_RIGHT: // 右だけが押されている場合
        obj->transform_->velocity_.x += getParam()->ACCEL_X;
        obj->getComponent<ActorComponent>()->xFlip_ = false;
        if (obj->getComponent<ActorComponent>()->onGround_)
        {
        obj->getComponent<Renderer>()->animeData_ = getParam()->ANIME_RIGHT;
        }
        break;
    default:        // どちらも押されていないか相殺されている場合
        obj->transform_->velocity_.x = 0;

        if (obj->getComponent<ActorComponent>()->onGround_)
        {
            if (obj->getComponent<ActorComponent>()->xFlip_)
            {
                obj->getComponent<Renderer>()->animeData_ = getParam()->ANIME_IDLE_LEFT;
            }
            else if (obj->getComponent<ActorComponent>()->xFlip_ == false )
            {
                obj->getComponent<Renderer>()->animeData_ = getParam()->ANIME_IDLE_RIGHT;
            }
        }

        break;
    }
    if (obj->getComponent<ActorComponent>()->dashingTimer_ > 0)
    {
    obj->getComponent<ActorComponent>()->dashingTimer_--;

    }
    ActorBehavior::moveX(obj);
}

void playerJumpSet(std::shared_ptr<OBJ2D> obj)
{
}

void BasePlayerBehavior::hitrect(std::shared_ptr<OBJ2D> src, std::shared_ptr<OBJ2D> dst) const
{
    
}

void BasePlayerBehavior::counter(std::shared_ptr<OBJ2D> obj)const
{
 
}

bool BasePlayerBehavior::isAlive(std::shared_ptr<OBJ2D>) const
{
    return true;    // 生存している（仮）
}

void BasePlayerBehavior::damageProc(std::shared_ptr<OBJ2D>obj) const
{
    // 入力処理
    //obj->getComponent<ActorComponent>()->padTrg_ = GameLib::input::TRG(0);
    obj->getComponent<ActorComponent>()->padState_ = GameLib::input::STATE(0);

    // ダメージ処理
    obj->getComponent<ActorComponent>()->damaged();

    // 無敵処理
    obj->getComponent<ActorComponent>()->invisible();
}

WalkPlayerBehavior::WalkPlayerBehavior()
{
    
    param_.ACCEL_X = 12.0f;
    param_.ACCEL_Y = 0;
    param_.SPEED_X_MAX = 12.0f;
    param_.SPEED_Y_MAX = 0.0f;
    param_.JUMP_POWER_Y = -20.0f;
    param_.HIT_BOX = { -60,-110,60,110 };
    param_.DUSH_POWER = 30.0f;
}

void WalkPlayerBehavior::moveY(std::shared_ptr<OBJ2D>  obj) const
{
    // 速度に加速度を加える
    //obj->transform_->velocity_.y += getParam()->ACCEL_Y;
   

    ActorBehavior::moveY(obj);
}

void WalkPlayerBehavior::jump(std::shared_ptr<OBJ2D>  obj) const
{
   
 
}

