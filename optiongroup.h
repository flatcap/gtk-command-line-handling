#ifndef _OPTIONGROUP_H_
#define _OPTIONGROUP_H_

#include <vector>
#include <string>

#include <glibmm/optiongroup.h>

class OptionGroup : public Glib::OptionGroup
{
public:
	OptionGroup();

	bool app        = false;
	bool list       = false;
	bool dot        = false;
	bool separate   = false;
	bool properties = false;

	int x = -1;	// Window coordinates
	int y = -1;
	int w = -1;	// Window size
	int h = -1;

	std::vector<std::string> config;
	std::vector<std::string> theme;
};

#endif // _OPTIONGROUP_H_

