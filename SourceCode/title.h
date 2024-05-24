#pragma once
#include"scene.h"
class Title : public Scene
{
private:
	static Title instance_;
	int scene_change_timer;
	float bg_opacity_;
	float fg_opacity_;
	float rect_size_x;
	float rect_size_y;
	bool flag_=true;
	bool rect_flag_;
	bool scene_change_flag_;


public:

	static Title* instance() { return &instance_; }

	void update() override;
	void draw() override;

private:
	Title() {}
	Title(const Title&) = delete;

};
