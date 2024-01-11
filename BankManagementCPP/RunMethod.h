#pragma once
#include "MainMenu.h"
#include "IRunMethod.h"
class RunMethod : public IRunMethod {

public:
	MainMenu* m = new MainMenu;
	RunMethod() {
	}
	void Run() override {
		while (1) {
			m->MainMenuStructure();
			m->AfterLoginMenu();
		}
	}
};