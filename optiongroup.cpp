#include <iostream>

#include "optiongroup.h"

OptionGroup::OptionGroup() :
	Glib::OptionGroup ("example_group", "description of example group", "help description of example group"),
	m_arg_foo (0)
{
	//These are just two pointless command-line arguments to show the use
	//of the API:
	Glib::OptionEntry entry1;
	entry1.set_long_name ("foo");
	entry1.set_short_name ('f');
	entry1.set_description ("Enable foo.");
	add_entry (entry1, m_arg_foo);

	Glib::OptionEntry entry2;
	entry2.set_long_name ("goo");
	entry2.set_short_name ('g');
	entry2.set_description ("The name of goo to use.");
	add_entry_filename (entry2, m_arg_goo);
}

void OptionGroup::on_error (Glib::OptionContext& /* context */, Glib::OptionGroup& /* group */)
{
	std::cout << "on_error called" << std::endl;
}

