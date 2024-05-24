#include"obj2d.h"
#include"../GameLib/game_lib.h"
#include"collider.h"
#include"sprite_data.h"
#include<list>
#include "game.h"

OBJ2D::OBJ2D()
    : transform_(std::make_shared< Transform>())
{
    components_.reserve(8);
    components_.emplace_back(transform_);
}

//OBJ2D::~OBJ2D()
//{
//
//    components_.clear();
//}
void OBJ2D::move()
{
    if (behavior_) behavior_->move(shared_from_this());
    //if (eraser_) eraser_->erase(shared_from_this());
}
void Renderer::draw(const VECTOR2& scrollPos)
{
    if (data_)
    {
        data_->draw(obj_->transform_->position_ - scrollPos,
            obj_->transform_->scale_, obj_->transform_->rotation_, color_);  // dataのdrawメソッドでスプライトを描画する
    }
}
//  戻り値：true  アニメが先頭に戻る瞬間
//        :false それ以外
bool Renderer::animeUpdate()
{
    if (animeData_ == nullptr)
    {
        assert(!"animeUpdate関数でAnimeDataがnullptr");
        return false;
    }

    if (anime_.pPrev != animeData_)         // アニメデータが切り替わったとき
    {
        anime_.pPrev = animeData_;
        anime_.patNum = 0;	                // 先頭から再生
        anime_.frame = 0;
    }

    animeData_ += anime_.patNum;
    data_ = animeData_->data;               // 現在のパターン番号に該当する画像を設定

    anime_.frame++;
    if (anime_.frame >= animeData_->frame)  // 設定フレーム数表示したら
    {
        anime_.frame = 0;
        anime_.patNum++;                    // 次のパターンへ
        if ((animeData_ + 1)->frame < 0)    // 終了コードのとき
        {
            anime_.patNum = 0;              // 先頭へ戻る
            return true;
        }
    }

    return false;
}
void OBJ2DManager::init()
{
    //リストのOBJ2Dを全てクリアする
    objList_.clear();

}
std::shared_ptr<OBJ2D> OBJ2DManager::add(std::shared_ptr<OBJ2D> obj, std::shared_ptr<Behavior> behavior, const VECTOR2& pos)
{
    obj->behavior_ = behavior;           // behavior_に引数のbehaviorを代入
    obj->transform_->position_ = pos;                // position_に引数のposを代入
    obj->addComponent<Renderer>();
    obj->addComponent<Collider>();
    objList_.emplace_back(obj);            // リストにobjを追加する
    return obj;       // 今追加したobjのアドレスを返す（何かで使えるように）
}
std::shared_ptr<OBJ2D> OBJ2DManager::insert(std::list<std::shared_ptr<OBJ2D>>::iterator& iter, std::shared_ptr<OBJ2D> obj, std::shared_ptr<Behavior> behavior, const VECTOR2& pos)
{
    obj->behavior_ = behavior;
    obj->transform_->position_ = pos;
    objList_.insert(iter,obj);
    return obj;
}
void OBJ2DManager::update()
{
    // 移動
    for (auto& obj : objList_)   // objListの全ての要素をループし、itという名前で各要素にアクセス
    {
        obj->move(); 
        obj->timer_++;// itのmoveメソッドを呼ぶ
       
    }

    // 空ノードの削除（今は気にしなくて良い）
    auto iter = objList_.begin();
    while (iter != objList_.end())
    {
        if ((*iter)->behavior_)
        {
            iter++;
        }
        else
        {

            iter = objList_.erase(iter);
        }
    }
}
bool predFunc(OBJ2D* obj1, OBJ2D* obj2)
{
    return obj1->zOrder_ < obj2->zOrder_;
}
void OBJ2DManager::draw(const VECTOR2& scrollPos)
{
    constexpr float LIMIT = 256.0f;

    //objList_.sort(predFunc);
    objList_.sort([](std::shared_ptr<OBJ2D> obj1, std::shared_ptr<OBJ2D> obj2) { return obj1->zOrder_ < obj2->zOrder_; });

    for (auto& obj : objList_)
    {
        const VECTOR2 screenPos = obj->transform_->position_ - scrollPos;
        if (screenPos.x < -LIMIT ||
            screenPos.x > GameLib::window::getWidth() + LIMIT ||
            screenPos.y < -LIMIT ||
            screenPos.y > GameLib::window::getHeight() + LIMIT)
            continue;

        obj->getComponent<Renderer>()->draw(scrollPos);
        obj->getComponent<Collider>()->draw(scrollPos);
     
    }

}

void OBJ2DManager::clearupdate()
{
  auto iter = objList_.begin();
  while (iter != objList_.end())
  {
    if ((*iter)->behavior_)
    {
      iter++;
    }
    else
    {

      iter = objList_.erase(iter);
    }
  }
}
void Collider::draw(const VECTOR2& scrollPos)
{
   /* if (isDrawHitRect_)
    {
        VECTOR2 pos = VECTOR2(hitBox_.left, hitBox_.top) - scrollPos;
        VECTOR2 size = { hitBox_.right - hitBox_.left, hitBox_.bottom - hitBox_.top };
        VECTOR2 center{ 0, 0 };
        VECTOR4 blue{ 0,0,1,1.0f };
        GameLib::primitive::rect(pos, size, center, 0,blue);
    }

    if (isDrawAttackRect_)
    {
        VECTOR2 pos = VECTOR2(attackBox_.left, attackBox_.top) - scrollPos;
        VECTOR2 size = { attackBox_.right - attackBox_.left, attackBox_.bottom - attackBox_.top };
        VECTOR2 center{ 0, 0 };
        VECTOR4 red{ 1,0,0,0.5f };
        GameLib::primitive::rect(pos, size, center, 0, red);
    }

    if (radius_ != 0)
    {
        GameLib::primitive::circle({ obj_->transform_->position_.x-scrollPos.x,obj_->transform_->position_.y-scrollPos.y }, radius_, { 1, 1 }, 0, { 1,0,0,1 });
    }*/
}

void Collider::calcHitBox(const GameLib::fRECT& rc)
{
    hitBox_ = {
        obj_->transform_->position_.x + rc.left,
        obj_->transform_->position_.y + rc.top,
        obj_->transform_->position_.x + rc.right,
        obj_->transform_->position_.y + rc.bottom
    };
}


void Collider::calcAttackBox(const GameLib::fRECT& rc)
{
    attackBox_ = {
        obj_->transform_->position_.x + rc.left,
        obj_->transform_->position_.y + rc.top,
        obj_->transform_->position_.x + rc.right,
        obj_->transform_->position_.y + rc.bottom
    };
}

bool Collider::hitCheckCircle(std::shared_ptr<Collider> other,VECTOR2 other_position)//当たっているかの確認
{
    float dx =  other_position.x-obj_->transform_->position_.x;
    float dy =  other_position.y- obj_->transform_->position_.y;
    float total_radius =  obj_->getComponent<Collider>()->radius_ + other->radius_;
    // 計算コスト削減のためにsqrtは使わない
    return (dx * dx + dy * dy) <= total_radius * total_radius;

}

bool Collider::hitCheckRect(std::shared_ptr<Collider> other)
{
  if (attackBox_.right >= other->hitBox_.left &&
    attackBox_.left <= other->hitBox_.right &&
    attackBox_.bottom >= other->hitBox_.top &&
    attackBox_.top <= other->hitBox_.bottom) return true;

  return false;
    /*if (attackBox_.right < other->hitBox_.left ||
        attackBox_.left > other->hitBox_.right ||
        attackBox_.bottom < other->hitBox_.top ||
        attackBox_.top > other->hitBox_.bottom) return false;

    return true;*/
}


bool Collider::hitCheck_Rect_Circle(std::shared_ptr<Collider>other, VECTOR2 other_position)
{
    bool nResult = false;

    // 四角形の四辺に対して円の半径分だけ足したとき円が重なっていたら
    if ((obj_->transform_->position_.x -obj_->getComponent<Renderer>()->Texsize_.x*2 < other->hitBox_.left - obj_->getComponent<Collider>()->radius_) &&
        (obj_->transform_->position_.x +obj_->getComponent<Renderer>()->Texsize_.x*2 > other->hitBox_.right + obj_->getComponent<Collider>()->radius_) &&
        (obj_->transform_->position_.y -obj_->getComponent<Renderer>()->Texsize_.y*2 < other->hitBox_.top - obj_->getComponent<Collider>()->radius_) &&
        (obj_->transform_->position_.y +obj_->getComponent<Renderer>()->Texsize_.y*2 > other->hitBox_.bottom + obj_->getComponent<Collider>()->radius_))
    {
        nResult = true;
        float fl = obj_->getComponent<Collider>()->radius_ * obj_->getComponent<Collider>()->radius_;


        // 左
        if (obj_->transform_->position_.x+ obj_->getComponent<Renderer>()->Texsize_.x > other->hitBox_.left )
        {
            // 左上
            if ((obj_->transform_->position_.y+ obj_->getComponent<Renderer>()->Texsize_.y > other->hitBox_.top))
            {
                if (sqrtf(((obj_->transform_->position_.x+ obj_->getComponent<Renderer>()->Texsize_.x - other->hitBox_.left)* 
                    (obj_->transform_->position_.x+ obj_->getComponent<Renderer>()->Texsize_.x - other->hitBox_.left))+((obj_->transform_->position_.y+ obj_->getComponent<Renderer>()->Texsize_.y- other->hitBox_.top)*
                        (obj_->transform_->position_.y+ obj_->getComponent<Renderer>()->Texsize_.y - other->hitBox_.top))) >= fl)
                {
                    nResult = false;
                }
            }
            else
            {
                // 左下
                if ((obj_->transform_->position_.y+ obj_->getComponent<Renderer>()->Texsize_.y < other->hitBox_.bottom))
                {
                    if (sqrtf(((obj_->transform_->position_.x+ obj_->getComponent<Renderer>()->Texsize_.x - other->hitBox_.left) *
                        (obj_->transform_->position_.x+ obj_->getComponent<Renderer>()->Texsize_.x - other->hitBox_.left)) +
                        ((obj_->transform_->position_.y + obj_->getComponent<Renderer>()->Texsize_.y- other->hitBox_.bottom) *
                            (obj_->transform_->position_.y+ obj_->getComponent<Renderer>()->Texsize_.y - other->hitBox_.bottom))) >= fl)
                    {
                        nResult = false;
                    }
                }
            }
        }
        else
        {
            // 右
            if (obj_->transform_->position_.x+ obj_->getComponent<Renderer>()->Texsize_.x < other->hitBox_.right)
            {
                // 右上
                if ((obj_->transform_->position_.y + obj_->getComponent<Renderer>()->Texsize_.y> other->hitBox_.top))
                {
                   // if ((DistanceSqrf(t_box.fRight, t_box.fTop, t_circle.x, t_circle.y) >= fl))
                    if (sqrtf(((obj_->transform_->position_.x+ obj_->getComponent<Renderer>()->Texsize_.x - other->hitBox_.right)
                        * (obj_->transform_->position_.x+ obj_->getComponent<Renderer>()->Texsize_.x - other->hitBox_.right))
                        + ((obj_->transform_->position_.y + obj_->getComponent<Renderer>()->Texsize_.y- other->hitBox_.top)
                            * (obj_->transform_->position_.y+ obj_->getComponent<Renderer>()->Texsize_.y - other->hitBox_.top))) >= fl)
                    {
                        nResult = false;
                    }
                }
                else
                {
                    // 右下
                    if ((obj_->transform_->position_.y + obj_->getComponent<Renderer>()->Texsize_.y< other->hitBox_.bottom))
                    {
                        if (sqrtf(((obj_->transform_->position_.x+ obj_->getComponent<Renderer>()->Texsize_.x - other->hitBox_.right)
                            * (obj_->transform_->position_.x+ obj_->getComponent<Renderer>()->Texsize_.x - other->hitBox_.right))
                            + ((obj_->transform_->position_.y+ obj_->getComponent<Renderer>()->Texsize_.y - other->hitBox_.bottom)
                                * (obj_->transform_->position_.y+ obj_->getComponent<Renderer>()->Texsize_.y - other->hitBox_.bottom))) >= fl)
                        {
                            nResult = false;
                        }
                    }
                }
            }
        }
    }

    return nResult;
}

bool Collider::hitCheck_Circle_Rect(std::shared_ptr<Collider>other,VECTOR2 other_position)
{
    // 円の中心座標
    float circleX = obj_->transform_->position_.x ;
    float circleY = obj_->transform_->position_.y ;

    // 矩形の左上隅の座標
    float rectX1 =  other->hitBox_.left;
    float rectY1 =  other->hitBox_.top;

    // 矩形の右下隅の座標
    float rectX2 =  other->hitBox_.right;
    float rectY2 =  other->hitBox_.bottom;

    float closestX = 0;
    float closestY = 0;

    if (circleX >= rectX1 && circleX <= rectX2 && circleY >= rectY1 && circleY <= rectY2) {
        return true;  // 円が矩形内にある場合
    }

   

}


bool Collider::hitCheckRectConfig(std::shared_ptr<OBJ2D> obj)
{
    return hitCheckRect(obj->getComponent<Collider>());
}

bool Collider::hitCheckCircleConfig(std::shared_ptr<OBJ2D> obj)
{
    return hitCheckCircle(obj->getComponent<Collider>(),obj->transform_->position_);
}

bool Collider::hitCheck_Circle_Rect_Config(std::shared_ptr<OBJ2D> obj)
{
    return hitCheck_Circle_Rect(obj->getComponent<Collider>(), obj->transform_->position_);
}
bool Collider::hitCheck_Rect_Circle_Config(std::shared_ptr<OBJ2D> obj) 
{
    return hitCheck_Rect_Circle(obj->getComponent<Collider>(), obj->transform_->position_);
}

void ActorComponent::damaged()
{
    if (damageTimer_ <= 0) return;

    padTrg_ = 0;
    padState_ = 0;
    --damageTimer_;
}

void ActorComponent::invisible()
{
    if (invisibleTimer_ <= 0) return;

    VECTOR4 color = obj_->getComponent<Renderer>()->color_;
    color.w = 0.0f;
    if (invisibleTimer_ & 0x01)
        color.w = 1.0f;
    obj_->getComponent<Renderer>()->color_ = color;

    --invisibleTimer_;
}

