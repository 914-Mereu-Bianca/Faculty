#pragma once
#include "Service.h"
#include "Validator.h"

class UI
{

private:
	Service &service;

	void admin_commands();
	void user_commands();
	void administrator_mode();
	void user_mode();

public:
	UI(Service &service);
	void start();

};

