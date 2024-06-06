#pragma once
#include"scene.h"
#ifndef INCLUDED_TITLE
#define	INCLUDED_TITLE
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

	void init(); 
	void deinit();
	void update() override;
	void draw() override;

private:
	Title() {}
	Title(const Title&) = delete;
};

#endif // !INCLUDED_TITLE
