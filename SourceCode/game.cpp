#include"game.h"
#include"../GameLib/game_lib.h"
#include"title.h"
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
    GameLib::texture::releaseAll();

    // ���y�̃N���A
    GameLib::music::clear();
}

void Game::update()
{

    switch (state_)
    {
    case 0:
        //////// �����ݒ� ////////
       
        GameLib::music::play(MUSIC_GAME, false);
        
        timer_ = 0;

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        GameLib::texture::load(loadTexture);

        // �v���C���[�}�l�[�W���̏�����
        obj2dManager()->init();

        // �v���C���[��ǉ�����
        player_ = obj2dManager()->add(
            std::make_shared<OBJ2D>(),
            walkPlayerBehavior,
            VECTOR2(-400, 1080 / 2)
        );
        player_->addComponent<Renderer>();
        player_->addComponent<Collider>();
        player_->addComponent<ActorComponent>();
       

        bg()->init(&player_->transform_->position_);
       
    
        player_->getComponent<ActorComponent>()->hit_timer_ = 0;
       
        player_->getComponent<ActorComponent>()->isAlive_ = true;
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
    GameLib::clear(VECTOR4(0, 0, 1, 1));
    DepthStencil::instance().set(DepthStencil::MODE::NONE);
    DepthStencil::instance().set(DepthStencil::MODE::MASK);

    DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);

   

    obj2dManager()->draw(bg()->getScrollPos());





  
    DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);
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



