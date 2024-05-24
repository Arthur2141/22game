#pragma once
#include"scene.h"
class Retry : public Scene
{
private:
	static Retry instance_;

public:
	static Retry* instance() { return &instance_; }

	void update() override;
	void draw() override;

private:
	Retry() {}
	Retry(const Retry&) = delete;
};
