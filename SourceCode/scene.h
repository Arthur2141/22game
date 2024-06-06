#pragma once
class Scene
{
protected:
    int state_;          // ���
    int timer_;          // �^�C�}�[
    int selection;      // �V�[���J�ڃR�}���h
    float fade;          //�t�F�[�h�C���A�t�F�[�h�A�E�g�p�����x
    Scene* nextScene_;   // ���̃V�[��

public:
    Scene* execute();   // ���s����

    virtual void init()
    { // ����������
        state_ = 0;
        timer_ = 0;
        selection = 0;
        fade = 0.0f;
        nextScene_ = nullptr;
    };
    virtual void deinit() {};   // �I������
    virtual void update() = 0;  // �X�V����
    virtual void draw() = 0;    // �`�揈��

    void changeScene(Scene* scene) { nextScene_ = scene; }   // �V�[���ύX����
    Scene* getScene() const { return nextScene_; }     
    void changeSelection(int s) { selection = s; }// nextScene�̃Q�b�^�[
};

class SceneManager
{
public:
    void execute(Scene*);  // ���s����
};