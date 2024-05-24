#include "game.h"
#include"actor.h"
void ActorBehavior::moveY(std::shared_ptr<OBJ2D> obj) const
{
    // Y方向の抗力の計算
    //obj->transform_->velocity_.y += obj->bg_->calcResistance(obj, obj->transform_->velocity_.y);

    // 最大速度チェックを行う
   // obj->transform_->velocity_.y = clamp(obj->transform_->velocity_.y, -getParam()->SPEED_Y_MAX, getParam()->SPEED_Y_MAX);

    // 位置更新
    float oldY = obj->transform_->position_.y;           // 移動前の位置を保持
    obj->transform_->position_.y += obj->transform_->velocity_.y;
    float deltaY = obj->transform_->position_.y - oldY;  // 移動後の位置から移動前の位置を引く

   // obj->getComponent<ActorComponent>()->onGround_ = false;

    // 下方向のあたり判定
    if (deltaY > 0)
    {
       // if (obj->bg_->isFloor(obj->transform_->position_.x, obj->transform_->position_.y, obj->getComponent<Collider>()->size_.x))
        {
            // 床にあたっていたら
        //    obj->bg_->mapHoseiDown(obj);    //  下方向の補正処理
        //    obj->getComponent<ActorComponent>()->onGround_ = true;   // 地面フラグ
        }
    }

    // 上方向のあたり判定
    if (deltaY < 0)
    {
       // if (obj->bg_->isCeiling(obj->transform_->position_.x, obj->transform_->position_.y - obj->getComponent<Collider>()->size_.y, obj->getComponent<Collider>()->size_.x))
       // {
            // 天井にあたっていたら
       //     obj->bg_->mapHoseiUp(obj);
       //     obj->getComponent<ActorComponent>()->jumpTimer_ = 0;
       // }
    }
}

void ActorBehavior::moveX(std::shared_ptr<OBJ2D> obj) const
{

    // 最大速度チェック
    if (obj->transform_->velocity_.x > getParam()->SPEED_X_MAX) obj->transform_->velocity_.x = getParam()->SPEED_X_MAX;
    if (obj->transform_->velocity_.x < -getParam()->SPEED_X_MAX) obj->transform_->velocity_.x = -getParam()->SPEED_X_MAX;

    // X方向移動
    float oldX = obj->transform_->position_.x;
    obj->transform_->position_.x += obj->transform_->velocity_.x;
    float deltaX = obj->transform_->position_.x - oldX;


}

void ActorBehavior::move(std::shared_ptr<OBJ2D>obj) const
{
    obj->getComponent<Renderer>()->animeData_ = nullptr;
    switch (obj->state_)
    {
    case 0:
        //////// 初期設定 ////////
        // アニメの初期設定
        obj->getComponent<Renderer>()->animeData_ = getParam()->ANIME_IDLE_RIGHT;
        obj->transform_->scale_ = getParam()->SCALE;
        obj->getComponent<Collider>()->size_ = {
            getParam()->SIZE.x * getParam()->SCALE.x,
            getParam()->SIZE.y * getParam()->SCALE.y
        };
       // obj->getComponent<ActorComponent>()->hp_ = getParam()->HP;

        init(obj);

        obj->state_++;
        break;

    case 1:
        //////// 通常時 ////////
        
        if (!isAlive(obj))
            break;
        damageProc(obj);
        moveY(obj);
        moveX(obj);
        jump(obj);
        dash(obj);
        
     
        areaCheck(obj);
        //turn(obj);
        //attack(obj);
        break;
    }

    obj->getComponent<Collider>()->calcHitBox(getParam()->HIT_BOX);
    obj->getComponent<Collider>()->calcAttackBox(getParam()->ATTACK_BOX);
   
    // アニメーション更新
    if (obj->getComponent<Renderer>()->animeData_) obj->getComponent<Renderer>()->animeUpdate();
}

void ActorBehavior::areaCheck(std::shared_ptr<OBJ2D> obj) const
{
    if (obj->transform_->position_.x < -800 + obj->getComponent<Collider>()->size_.x)
    {
        obj->transform_->position_.x = -800 +obj->getComponent<Collider>()->size_.x;
        obj->transform_->velocity_.x = 0;

        obj->getComponent<ActorComponent>()->kabeFlag_ = true;
    }
    if (obj->transform_->position_.x > 2700 - obj->getComponent<Collider>()->size_.x)
    {
       obj->transform_->position_.x = 2700 - obj->getComponent<Collider>()->size_.x;
       obj->transform_->velocity_.x = 0;

       obj->getComponent<ActorComponent>()->kabeFlag_ = true;
    } 
    if (obj->transform_->position_.y < 250 + obj->getComponent<Collider>()->size_.y)
    {
        obj->transform_->position_.y = 250 +obj->getComponent<Collider>()->size_.y;
       // obj->transform_->velocity_.y = 0;

        obj->getComponent<ActorComponent>()->kabeFlag_ = true;
    }
    if (obj->transform_->position_.y > 850 - obj->getComponent<Collider>()->size_.y)
    {
       obj->transform_->position_.y = 850 - obj->getComponent<Collider>()->size_.y;
      // obj->transform_->velocity_.y = 0;
       obj->getComponent<ActorComponent>()->onGround_ = true;
       obj->getComponent<ActorComponent>()->kabeFlag_ = true;
    }
}
