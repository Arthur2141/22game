#pragma once
#include"scene.h"
class Clear : public Scene
{
private:
	static Clear instance_;

public:
	static Clear* instance() { return &instance_; }

	void update() override;
	void draw() override;

private:
	Clear() {}
	Clear(const Clear&) = delete;
};
