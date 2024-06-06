#pragma once
#include <list>
#include <vector>
#include "../GameLib/vector.h"
#include "../GameLib/obj2d_data.h"
//#include "../stage.h"
class OBJ2D;

enum class OBJ_TYPE
{
    PLAYER,
    ENEMY,
    PROJECTILE,
    COUNTER,
    UI,
    AREA,
    SCAFFOLD,
};

// 移動アルゴリズムクラス（抽象クラス）
class Behavior
{
  
public:
    virtual void move(std::shared_ptr<OBJ2D>obj) const = 0;
    virtual OBJ_TYPE getType() const = 0;
    virtual OBJ_TYPE getAttackType() const = 0;
    virtual void hitrect(std::shared_ptr<OBJ2D> src, std::shared_ptr<OBJ2D> dst) const = 0;
};

// 消去アルゴリズムクラス（抽象クラス）
class Eraser
{
public:
    virtual void erase(std::shared_ptr<OBJ2D> obj) const = 0;
};

class Component
{
protected:
    std::shared_ptr<OBJ2D> obj_;

public:
    Component()
        :obj_()
    {
    }
    virtual void draw(const VECTOR2&) {}
    void setOBJ2D(std::shared_ptr<OBJ2D> obj) { obj_ = obj; }
};

class Transform : public Component
{
public:
    VECTOR2 position_;
    VECTOR2 scale_;
    
    float rotation_;
    VECTOR2 velocity_;

    Transform()
        :position_()
        , scale_({ 1,1 })
        , rotation_()
        , velocity_()
    {
    }
};

class Renderer : public Component
{
public:
    GameLib::SpriteData* data_;
    VECTOR4 color_;
    GameLib::Anime anime_;
    GameLib::AnimeData* animeData_;
    VECTOR2 Texsize_;

    Renderer()
        :data_()
        , color_({ 1,1,1,1 })
        , anime_()
        , animeData_()
    {
    }
    void draw(const VECTOR2& scrollPos) override;
    bool animeUpdate();
};

class Collider : public Component
{
public:
    VECTOR2 size_;
    VECTOR2 offset;

    GameLib::fRECT hitBox_;
    GameLib::fRECT hitSize_;
    GameLib::fRECT attackBox_;

    
    float radius_;
    float attackRadius_;

    bool judgeFlag_;
    bool isDrawHitRect_;
    bool isDrawAttackRect_;

    Collider()
        :size_()
        , judgeFlag_()
        , isDrawHitRect_()
        , isDrawAttackRect_()
        , hitBox_()
        ,hitSize_()
        , attackBox_()
      ,offset()
      ,radius_()
      ,attackRadius_()
    {
    }

    void draw(const VECTOR2& scrollPos) override;
    void calcHitBox(const GameLib::fRECT& rc);
    void calcAttackBox(const GameLib::fRECT& rc);

    void calcHitCircle(const GameLib::fRECT& rc);

    void calcAttackCircle(const float radius);

    bool hitCheckRect(std::shared_ptr<Collider> other);
    bool hitCheckCircle(std::shared_ptr<Collider> other,VECTOR2 other_position);
    bool hitCheck_Rect_Circle(std::shared_ptr<Collider>other, VECTOR2 other_position);
    bool hitCheck_Circle_Rect(std::shared_ptr<Collider>other,VECTOR2 othe_position);

    bool hitCheckRectConfig(std::shared_ptr<OBJ2D> obj);
    bool hitCheckCircleConfig(std::shared_ptr<OBJ2D> obj);
    bool hitCheck_Rect_Circle_Config(std::shared_ptr<OBJ2D> obj);
    bool hitCheck_Circle_Rect_Config(std::shared_ptr<OBJ2D> obj);

};

class ActorComponent : public Component
{
public:
    int jumpTimer_;
    int hp_;
    int power_;
    int attackTimer_;
    int damageTimer_;
    int dashingTimer_;
    int dashcoolTimer_;
    int invisibleTimer_;
    int padTrg_;
    int padState_;
    int hit_timer_;
    int shield_break_time_;
    float tama_color_;
    bool isAlive_;
    bool onGround_;
    bool kabeFlag_;
    bool gakeFlag_;
    bool xFlip_;
    bool succsesCounter_;
    bool shield_Alive_;
    bool hit_;


    ActorComponent()
        :jumpTimer_()
        , onGround_(false)
        , kabeFlag_(false)
        , gakeFlag_(false)
        , xFlip_(false)
        , succsesCounter_(false)
        ,shield_Alive_(true)
        , hp_(1)
        , attackTimer_(0)
        , damageTimer_(0)
        , invisibleTimer_(0)
        , padTrg_(0)
        , padState_(0)
        ,power_(100)
        ,dashingTimer_(0)
        ,dashcoolTimer_(0)
        
    {
    }
    void flip() { xFlip_ = !xFlip_; }
    bool isAlive() const { return hp_ > 0; }
    void damaged();
    void invisible();

};

class BG;
class UI;

class OBJ2D:public std::enable_shared_from_this<OBJ2D>
{
public:
    
    // 基本的なメンバ
    int state_ = 0;
    int timer_ = 0;
    int zOrder_ = 0;
    //StagePath targetP = {};
    std::shared_ptr<Behavior> behavior_ = nullptr;
    std::shared_ptr<Eraser> eraser_ = nullptr;
    std::shared_ptr<BG> bg_ = nullptr;
    std::shared_ptr<UI> ui_ = nullptr;
    std::shared_ptr<Transform> transform_;
    std::vector<std::shared_ptr<Component>> components_;
    int GetState() { return state_; }
    GameLib::SpriteData* GetData() const { return data_; }

    template<typename T>std::shared_ptr<T> addComponent() {
        std::shared_ptr<T> comp = std::make_shared<T>();
        comp->setOBJ2D(shared_from_this());
        components_.emplace_back(comp);
        return comp;
    }
    template<typename T>std::shared_ptr<T> getComponent() {
        for (auto& comp : components_) {
            if (typeid(*comp) != typeid(T))continue;
            return std::static_pointer_cast<T>(comp);
        }
        return nullptr;
    }
    OBJ2D();
    void move();    // 移動
    void setBG(std::shared_ptr<BG> bg) { bg_ = bg; }
    void remove() { behavior_ = nullptr; }
    void setBehavior(std::shared_ptr<Behavior> behavior)
    {
        behavior_ = behavior;
        state_ = 0;
    }
private:
    GameLib::SpriteData* data_;

};

class OBJ2DManager
{
private:
    VECTOR2* scrollPos_;
protected:
    std::list<std::shared_ptr<OBJ2D>> objList_;
public:
    
    void setScrollPos(VECTOR2* s) { scrollPos_ = s; }

    void init();    // 初期化
    void update();  // 更新
    void draw(const VECTOR2&);    // 描画
    void clearupdate();

    std::shared_ptr<OBJ2D> add(std::shared_ptr<OBJ2D> obj, std::shared_ptr<Behavior> behavior, const VECTOR2& pos);
    std::shared_ptr<OBJ2D> insert(std::list<std::shared_ptr<OBJ2D>>::iterator& iter, std::shared_ptr<OBJ2D> obj, std::shared_ptr<Behavior> behavior, const VECTOR2& pos);
    std::list<std::shared_ptr<OBJ2D>>* getList() { return &objList_; }
};