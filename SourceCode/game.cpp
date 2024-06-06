#include"game.h"
#include <DirectXMath.h>
//#include"../GameLib/game_lib.h"
//#include"../GameLib/game_lib.h"
#include "../GameLib/input_manager.h"
#include "../GameLib/obj2d_data.h"
#include "../GameLib/depth_stencil.h"
#include"title.h"
#include"result.h"
#include"gameover.h"
#include"retry.h"
#include"clear.h"
#include"player.h"

#include"ui.h"
#include"sprite_data.h"
#include"bg.h"
#include"math.h"
#include <memory>

#include"../GameLib/depth_stencil.h"
#include"audio.h"

using namespace GameLib;
using namespace input;
Game Game::instance_;

bool hitStop;



void Game::init()
{
    Scene::init();	    // ���N���X��init���Ă�
    obj2dManager_ = std::make_shared<OBJ2DManager>();
    walkPlayerBehavior = std::make_shared<WalkPlayerBehavior>();
   
 
    bg_ = new BG;
    ui_ = new UI;

}

VECTOR2 playerPos()
{
  if (Game::instance())
  {
  return Game::instance()->getPlayer_Position();

  }
}

void Game::deinit()
{
    // �e�}�l�[�W���̉��
    //safe_delete(obj2dManager_);
  obj2dManager_->getList()->clear();
  player_->components_.clear();
  player_->behavior_.reset();
 
  //projectiles_.~shared_ptr();
  //obj2dManager_->getList().
  if (bg_)
  {
    delete bg_;
  }  if (ui_)
  {
    delete ui_;
  }
    // �e�N�X�`���̉��
    //GameLib::texture::releaseAll();

    // ���y�̃N���A
    GameLib::music::clear();
}

void Game::update()
{

    // w�L�[�iPAD_UP�j��s�L�[�iPAD_DOWN�j�̓���������RESULT�ɐ؂�ւ�
    if ((STATE(0) & PAD_UP) && (STATE(0) & PAD_DOWN))
    {
        changeScene(Gameover::instance());
        return; // ����ȏ�̍X�V������h�����߂ɑ������^�[��
    }

    // w�L�[�iPAD_UP�j��s�L�[�iPAD_DOWN�j�̓���������RESULT�ɐ؂�ւ�
    if ((STATE(0) & PAD_RIGHT) && (STATE(0) & PAD_LEFT))
    {
        changeScene(Result::instance());
        return; // ����ȏ�̍X�V������h�����߂ɑ������^�[��
    }

    switch (state_)
    {
    case 0:
        //////// �����ݒ� ////////
       
        GameLib::music::play(MUSIC_GAME, false);
        
        timer_ = 0;
        fade = 1.0f;

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        //texture::load(loadTexture);

        // �v���C���[�}�l�[�W���̏�����
        obj2dManager()->init();

        // �v���C���[��ǉ�����
        player_ = obj2dManager()->add(
            std::make_shared<OBJ2D>(),
            walkPlayerBehavior,
            VECTOR2(0, 1080 / 2)
        );
        player_->addComponent<Renderer>();
        player_->addComponent<Collider>();
        player_->addComponent<ActorComponent>();
       
        
        bg()->init(&player_->transform_->position_);
       
    
        player_->getComponent<ActorComponent>()->hit_timer_ = 0;
       
        player_->getComponent<ActorComponent>()->isAlive_ = true;
        state_++;
        break;
          // �����������̏I��
        /*fallthrough*/

    case 1:
        //////// �ʏ펞�̏��� ////////
        
      
        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();
      
        bg()->update();
        ui()->update();
        //bg()->update();   // BG�̍X�V
        judge();


        obj2dManager()->clearupdate();
        // �\�t�g���Z�b�g
   

     
        player_->getComponent<ActorComponent>()->hit_timer_--;

       


      

        break;
    }

    
}

void Game::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0, 0, 0, 1));

    texture::begin(TEXNO::GAME);
    texture::draw(TEXNO::GAME, { 0, 0 }, { 1, 1 }, { 0, 0 },
        { BG::WINDOW_W, BG::WINDOW_H }, { 0, 0 });
    texture::end(TEXNO::GAME);
    //DepthStencil::instance().set(DepthStencil::MODE::NONE);
    //DepthStencil::instance().set(DepthStencil::MODE::MASK);

    //DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);

   
   // GameLib::primitive::circle(player_->transform_->position_, 20, { 1,1 }, 0, { 1,1,1,1 });
    //obj2dManager()->draw(bg()->getScrollPos());
    GameLib::primitive::line(50, 400, 500, 100, 0, 1, 0, 1, 10);
    GameLib::primitive::line(500, 100, 700, 270, 0, 1, 0, 1, 10);
    GameLib::primitive::line(700, 270, 800, 400, 0, 1, 0, 1, 10);
    GameLib::primitive::line(800, 400, 900, 300, 0, 1, 0, 1, 10);
    GameLib::primitive::line(900, 300, 1000, 400, 0, 1, 0, 1, 10);
    GameLib::primitive::line(1000, 400, 1200, 100, 0, 1, 0, 1, 10);
    GameLib::primitive::line(1200, 100, 1300, 900, 0, 1, 0, 1, 10);
   
    //DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);
}

void Game::judge()
{
  for (auto& src : *obj2dManager_->getList())
  {
    if (src->behavior_ == nullptr) continue;
    if (src->getComponent<Collider>()->judgeFlag_ == false) continue;

    for (auto& dst : *obj2dManager_->getList())
    {
      if (src == dst) continue;
      if (src->behavior_ == nullptr) break;
      if (src->getComponent<Collider>()->judgeFlag_ == false) break;
      if (dst->behavior_ == nullptr) continue;
      if (dst->getComponent<Collider>()->judgeFlag_ == false) continue;

      // src�̍U���^�C�v��dst�̃^�C�v����v���Ȃ����continue;
      if (src->behavior_->getAttackType() != dst->behavior_->getType())
        continue;

      // �����蔻����s��
      if (src->getComponent<Collider>()->hitCheckRectConfig(dst))//�����͂������Ƃ�����
      {
        // ���������ꍇ�̏���
        src->behavior_->hitrect(src, dst);
        continue;
      }
      if (src->getComponent<Collider>()->hitCheckCircleConfig(dst))//�����~�Ɖ~
      {
        //src->behavior_
        src->behavior_->hitrect(src, dst);
        continue;
      }
      if (src->getComponent<Collider>()->hitCheck_Rect_Circle_Config(dst))
      {
        src->behavior_->hitrect(src, dst);
        continue;
      }
    }
  }


}




