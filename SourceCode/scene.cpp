#include"../GameLib/game_lib.h"
#include"../GameLib/depth_stencil.h"
#include"scene.h"
#include"common.h"
#include"audio.h"
Scene* Scene::execute()
{

    // ����������
    init();

    // �Q�[�����[�v
    while (GameLib::gameLoop(false))    // false��true�ɂ���ƃ^�C�g���o�[�Ƀt���[�����[�g�\��
    {
        // ���͏���
        GameLib::input::update();

        // �X�V����
        update();

        // �X�e���V�����[�h�F�ʏ�
        DepthStencil::instance().set(DepthStencil::MODE::NONE);

        // �`�揈��
        draw();

        // �X�e���V�����[�h�F�ʏ�
        DepthStencil::instance().set(DepthStencil::MODE::NONE);

        // �f�o�b�O������̕`��
        GameLib::debug::display(1, 1, 1, 1, 1);
        //debug::setString("GP2_12 SAMPLE");

        // ��ʃt���b�v
        GameLib::present(1, 0);

        // �I���`�F�b�N
        if (nextScene_) break;
    }

    // �I������
    deinit();

    return nextScene_;	// ���̃V�[����Ԃ�
}

void SceneManager::execute(Scene* scene)
{

    using namespace GameLib;

    bool isFullScreen = false;	// �t���X�N���[���ɂ���Ȃ�true�ɕς���
    //�iRelease���[�h�̂݁j

// �Q�[�����C�u�����̏���������
    int w = static_cast<int>(SCREEN_W);
    int h = static_cast<int>(SCREEN_H);
    GameLib::init(L"game2-2", w, h, isFullScreen);
    audio_init();
    GameLib::music::update();

#ifndef _DEBUG
    ShowCursor(!isFullScreen);	// �t���X�N���[�����̓J�[�\��������
#endif

    // ���C�����[�v
    while (scene)
    {
        scene = scene->execute();
    }

    // �Q�[�����C�u�����̏I������
    GameLib::uninit();
}
