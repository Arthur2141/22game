#pragma once

#include "scene.h"
//******************************************************************************
//
//
//      リザルトシーン
//
//
//******************************************************************************

//==============================================================================
//
//      Resultクラス
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
