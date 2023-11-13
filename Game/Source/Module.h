#ifndef __MODULE_H__
#define __MODULE_H__

#include "SString.h"

#include "PugiXml/src/pugixml.hpp"

class App;

class Module
{
public:

	Module() : active(false)
	{}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

public:

	SString name;
	bool active;

private:
	bool isEnabled = true;

public:
	

	void Module::Enable()
	{
		if (!isEnabled)
		{
			isEnabled = true;
			Start();
		}
	}

	void Module::Disable()
	{
		// TODO 0: Call CleanUp() for disabling a module
		if (isEnabled)
		{
			isEnabled = false;
			CleanUp();
		}
	}


};


#endif // __MODULE_H__