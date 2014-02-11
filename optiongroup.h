#ifndef _OPTIONGROUP_H_
#define _OPTIONGROUP_H_

#include <gtkmm.h>

class OptionGroup : public Glib::OptionGroup
{
public:
	OptionGroup();

	virtual void on_error (Glib::OptionContext& context, Glib::OptionGroup& group);

	bool m_arg_foo;
	std::string m_arg_goo;
};

#endif // _OPTIONGROUP_H_

