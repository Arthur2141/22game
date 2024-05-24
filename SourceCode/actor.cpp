#include "game.h"
#include"actor.h"
void ActorBehavior::moveY(std::shared_ptr<OBJ2D> obj) const
{
    // Y�����̍R�͂̌v�Z
    //obj->transform_->velocity_.y += obj->bg_->calcResistance(obj, obj->transform_->velocity_.y);

    // �ő呬�x�`�F�b�N���s��
   // obj->transform_->velocity_.y = clamp(obj->transform_->velocity_.y, -getParam()->SPEED_Y_MAX, getParam()->SPEED_Y_MAX);

    // �ʒu�X�V
    float oldY = obj->transform_->position_.y;           // �ړ��O�̈ʒu��ێ�
    obj->transform_->position_.y += obj->transform_->velocity_.y;
    float deltaY = obj->transform_->position_.y - oldY;  // �ړ���̈ʒu����ړ��O�̈ʒu������

   // obj->getComponent<ActorComponent>()->onGround_ = false;

    // �������̂����蔻��
    if (deltaY > 0)
    {
       // if (obj->bg_->isFloor(obj->transform_->position_.x, obj->transform_->position_.y, obj->getComponent<Collider>()->size_.x))
        {
            // ���ɂ������Ă�����
        //    obj->bg_->mapHoseiDown(obj);    //  �������̕␳����
        //    obj->getComponent<ActorComponent>()->onGround_ = true;   // �n�ʃt���O
        }
    }

    // ������̂����蔻��
    if (deltaY < 0)
    {
       // if (obj->bg_->isCeiling(obj->transform_->position_.x, obj->transform_->position_.y - obj->getComponent<Collider>()->size_.y, obj->getComponent<Collider>()->size_.x))
       // {
            // �V��ɂ������Ă�����
       //     obj->bg_->mapHoseiUp(obj);
       //     obj->getComponent<ActorComponent>()->jumpTimer_ = 0;
       // }
    }
}

void ActorBehavior::moveX(std::shared_ptr<OBJ2D> obj) const
{

    // �ő呬�x�`�F�b�N
    if (obj->transform_->velocity_.x > getParam()->SPEED_X_MAX) obj->transform_->velocity_.x = getParam()->SPEED_X_MAX;
    if (obj->transform_->velocity_.x < -getParam()->SPEED_X_MAX) obj->transform_->velocity_.x = -getParam()->SPEED_X_MAX;

    // X�����ړ�
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
        //////// �����ݒ� ////////
        // �A�j���̏����ݒ�
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
        //////// �ʏ펞 ////////
        
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
   
    // �A�j���[�V�����X�V
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
