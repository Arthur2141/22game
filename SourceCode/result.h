#pragma once

#include "scene.h"
//******************************************************************************
//
//
//      ���U���g�V�[��
//
//
//******************************************************************************

//==============================================================================
//
//      Result�N���X
//
//==============================================================================

class Result : public Scene
{
public:
    static constexpr float GROUND_POS_Y = 400.0f;

public:
    static Result* instance() { return &instance_; }

    void init();
    void deinit();
    void update();
    void draw();

private:
    static Result instance_;
};
