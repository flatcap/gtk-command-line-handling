#ifndef _OPTIONGROUP_H_
#define _OPTIONGROUP_H_

#include <gtkmm.h>

class OptionGroup : public Glib::OptionGroup
{
public:
	OptionGroup();

	virtual void on_error (Glib::OptionContext& context, Glib::OptionGroup& group);

	bool app      = false;
	bool list     = false;
	bool dot      = false;
	bool separate = false;

	std::vector<std::string> config;
	std::vector<std::string> theme;

	int x = -1;	// Window coordinates
	int y = -1;
	int w = -1;	// Window size
	int h = -1;
};

#endif // _OPTIONGROUP_H_

