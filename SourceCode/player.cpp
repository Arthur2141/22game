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
    obj->getComponent<Collider>()->isDrawAttackRect_ = false;
    obj->getComponent<Collider>()->radius_ = 0;
    obj->getComponent<Renderer>()->Texsize_ = { 700,700 };
    obj->transform_->scale_ = { 0.5f,0.5f };
    obj->getComponent<ActorComponent>()->hp_ = 3;
}

void BasePlayerBehavior::moveX(std::shared_ptr<OBJ2D> obj) const
{
 /* if (Game::instance()->cutsceneIn)
  {
    obj->getComponent<Renderer>()->animeData_ = getParam()->ANIME_RIGHT;
    return;

  }*/
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
    obj->transform_->velocity_.y = -8.0f;
    obj->getComponent<ActorComponent>()->jumpTimer_ = 12;
}

void BasePlayerBehavior::hitrect(std::shared_ptr<OBJ2D> src, std::shared_ptr<OBJ2D> dst) const
{
    /*if (src->getComponent<Collider>()->attackBox_.top >= dst->getComponent<Collider>()->hitBox_.top) return;
    if (src->transform_->velocity_.y <= 0.0f) return;
    dst->getComponent<ActorComponent>()->hp_ -= getParam()->ATTACK_POWER;
    playerJumpSet(src);*/
}

void BasePlayerBehavior::counter(std::shared_ptr<OBJ2D> obj)const
{
 /* if (Game::instance()->boss_->getComponent<ActorComponent>() < 0|| Game::instance()->player_->getComponent<ActorComponent>() < 0)
  {
    return;
  }*/
    if (obj->getComponent<ActorComponent>()->succsesCounter_)
    {
        if (obj->getComponent<ActorComponent>()->xFlip_)
        {
            obj->getComponent<Renderer>()->animeData_ = getParam()->ANIME_COUNTER_LEFT;
        }
        else
        {
            obj->getComponent<Renderer>()->animeData_ = getParam()->ANIME_COUNTER_RIGHT;
        }
        if (obj->getComponent<ActorComponent>()->xFlip_)
        {
            obj->transform_->rotation_ += 1;
        }
        else
        {
            obj->transform_->rotation_ -= 1;
        }
    }
        if (obj->getComponent<Renderer>()->animeData_) obj->getComponent<Renderer>()->animeUpdate();
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
    param_.ACCEL_Y = 1.5f;
    param_.SPEED_X_MAX = 12.0f;
    param_.SPEED_Y_MAX = 30.0f;
    param_.JUMP_POWER_Y = -20.0f;
    param_.HIT_BOX = { -60,-110,60,110 };
    param_.DUSH_POWER = 30.0f;
}

void WalkPlayerBehavior::moveY(std::shared_ptr<OBJ2D>  obj) const
{
    // 速度に加速度を加える
    obj->transform_->velocity_.y += getParam()->ACCEL_Y;
   

    ActorBehavior::moveY(obj);
}

void WalkPlayerBehavior::jump(std::shared_ptr<OBJ2D>  obj) const
{
    // ジャンプチェック
  if (!obj->getComponent<ActorComponent>()->onGround_)
  {
    if (obj->getComponent<ActorComponent>()->xFlip_)
    {
      obj->getComponent<Renderer>()->animeData_ = getParam()->ANIME_UP_LEFT;

    }
    else if (obj->getComponent<ActorComponent>()->xFlip_ == false)
    {
      obj->getComponent<Renderer>()->animeData_ = getParam()->ANIME_UP_RIGHT;
    }
  }
    if (GameLib::input::TRG(0) & GameLib::input::PAD_TRG4)
    {
        if (obj->getComponent<ActorComponent>()->onGround_)
        {
            obj->getComponent<ActorComponent>()->jumpTimer_ = 5;     
        }
         //obj->getComponent<ActorComponent>()->onGround_ = false;
    }

    // ジャンプ中
    if (obj->getComponent<ActorComponent>()->jumpTimer_ > 0)
    {
        if (obj->getComponent<ActorComponent>()->padState_ & GameLib::input::PAD_TRG4 )
        {   // PAD_TRG1が押されている場合

              obj->transform_->velocity_.y = getParam()->JUMP_POWER_Y;
            --obj->getComponent<ActorComponent>()->jumpTimer_;
            obj->getComponent<ActorComponent>()->onGround_ = false;
            

        }
        else
        {   // PAD_TRG1が押されていない場合
            obj->getComponent<ActorComponent>()->jumpTimer_ = 0;

        }
    }
    
}

//void WalkPlayerBehavior::dash(std::shared_ptr<OBJ2D>  obj) const
//{
//    // ジャンプチェック
//    if (obj->getComponent<ActorComponent>()->dashcoolTimer_ < 0)
//    {
//        obj->getComponent<ActorComponent>()->dashcoolTimer_ = 0;
//    } 
//    if (obj->getComponent<ActorComponent>()->dashingTimer_ < 0)
//    {
//        obj->getComponent<ActorComponent>()->dashingTimer_ = 0;
//    }  
//
//    if (GameLib::input::TRG(0) & GameLib::input::PAD_DOWN && obj->getComponent<ActorComponent>()->dashcoolTimer_ == 0&&obj->getComponent<ActorComponent>()->power_>10)
//    {
//        obj->getComponent<ActorComponent>()->dashcoolTimer_ = 150;
//        obj->getComponent<ActorComponent>()->dashingTimer_ = 30;
//        obj->getComponent<ActorComponent>()->power_ -= 10;
//    }
//
//    if (obj->getComponent<ActorComponent>()->dashingTimer_ > 0)
//    { 
//        if (GameLib::input::TRG(0) & GameLib::input::PAD_LEFT)
//        {
//            obj->transform_->velocity_.x -= getParam()->DUSH_POWER;
//            if (obj->getComponent<ActorComponent>()->dashingTimer_ == 0) {
//                obj->transform_->velocity_.x += 60.0f;
//            }
//        }
//        else if (GameLib::input::TRG(0) & GameLib::input::PAD_RIGHT)
//        {
//            obj->transform_->velocity_.x += getParam()->DUSH_POWER;
//            if (obj->getComponent<ActorComponent>()->dashingTimer_ == 0) {
//                obj->transform_->velocity_.x -= 60.0f;
//            }
//        }     
//        else if (GameLib::input::TRG(0) & GameLib::input::PAD_UP)
//        {
//            obj->transform_->velocity_.y += -getParam()->DUSH_POWER; 
//            if (obj->getComponent<ActorComponent>()->dashingTimer_ == 0) {
//                obj->transform_->velocity_.y += 60.0f;
//            }
//        } 
//       // else
//        //{   
//       //     obj->getComponent<ActorComponent>()->dashingTimer_ = 0;
//       // }
//    }
//
//        GameLib::debug::setString("dashcoolTimer_%d", obj->getComponent<ActorComponent>()->dashcoolTimer_);
//        GameLib::debug::setString("dashingTimer_%d", obj->getComponent<ActorComponent>()->dashingTimer_);
//        GameLib::debug::setString("speed%f", obj->transform_->velocity_.x);
//        --obj->getComponent<ActorComponent>()->dashcoolTimer_;
//        --obj->getComponent<ActorComponent>()->dashingTimer_;
//      
//            
//}