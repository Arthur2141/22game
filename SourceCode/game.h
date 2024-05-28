#pragma once
#include"scene.h"
#include"obj2d.h"

class Game : public Scene
{
private:
    std::shared_ptr<OBJ2DManager> obj2dManager_;
    BG*           bg_;
    UI*           ui_;
    
    static Game     instance_;
    //aababa
public:
  
    std::shared_ptr<OBJ2D> player_;
  
    static Game* instance() { return &instance_; }
    VECTOR2 getPlayer_Position() { return player_->transform_->position_; }

    bool getPlayerXflip_() { return player_->getComponent<ActorComponent>()->xFlip_; }
    bool getPlayerOnground_() { return player_->getComponent<ActorComponent>()->onGround_; }
    bool getPlayerIsalive_() { return player_->getComponent<ActorComponent>()->isAlive_; }
    std::shared_ptr<OBJ2DManager> obj2dManager() { return obj2dManager_; }
    BG* bg() { return bg_; }
    UI* ui() { return ui_; }
   
    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;
  
    
private:
    Game()
        :obj2dManager_(nullptr)
        , player_(nullptr) {}
    Game(const Game&) = delete; // = delete コピーコンストラクタが存在しないことを明示
    void judge();
  
};


