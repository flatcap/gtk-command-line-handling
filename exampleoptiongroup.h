#ifndef _EXAMPLEOPTIONGROUP_H_
#define _EXAMPLEOPTIONGROUP_H_

#include <gtkmm.h>

class ExampleOptionGroup : public Glib::OptionGroup
{
public:
	ExampleOptionGroup();

	virtual void on_error (Glib::OptionContext& context, Glib::OptionGroup& group);

	bool m_arg_foo;
	std::string m_arg_goo;
};

#endif // _EXAMPLEOPTIONGROUP_H_

