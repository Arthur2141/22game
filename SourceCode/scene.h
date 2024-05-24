#pragma once
class Scene
{
protected:
    int state_;          // 状態
    int timer_;          // タイマー
    Scene* nextScene_;   // 次のシーン

public:
    Scene* execute();   // 実行処理

    virtual void init()
    { // 初期化処理
        state_ = 0;
        timer_ = 0;
        nextScene_ = nullptr;
    };
    virtual void deinit() {};   // 終了処理
    virtual void update() = 0;  // 更新処理
    virtual void draw() = 0;    // 描画処理

    void changeScene(Scene* scene) { nextScene_ = scene; }   // シーン変更処理
    Scene* getScene() const { return nextScene_; }           // nextSceneのゲッター
};

class SceneManager
{
public:
    void execute(Scene*);  // 実行処理
};