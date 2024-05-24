#pragma once
class Scene
{
protected:
    int state_;          // ���
    int timer_;          // �^�C�}�[
    Scene* nextScene_;   // ���̃V�[��

public:
    Scene* execute();   // ���s����

    virtual void init()
    { // ����������
        state_ = 0;
        timer_ = 0;
        nextScene_ = nullptr;
    };
    virtual void deinit() {};   // �I������
    virtual void update() = 0;  // �X�V����
    virtual void draw() = 0;    // �`�揈��

    void changeScene(Scene* scene) { nextScene_ = scene; }   // �V�[���ύX����
    Scene* getScene() const { return nextScene_; }           // nextScene�̃Q�b�^�[
};

class SceneManager
{
public:
    void execute(Scene*);  // ���s����
};