#include <iostream>

#include "optiongroup.h"

OptionGroup::OptionGroup() :
	Glib::OptionGroup ("dparted", "Options for DParted", "Options to configure DParted")
{
	Glib::OptionEntry entry01;
	entry01.set_short_name ('a');
	entry01.set_long_name ("app");
	entry01.set_description ("Run the graphical application (default)");
	add_entry (entry01, app);

	Glib::OptionEntry entry02;
	entry02.set_short_name ('l');
	entry02.set_long_name ("list");
	entry02.set_description ("List all the metadata about the disks");
	add_entry (entry02, list);

	Glib::OptionEntry entry03;
	entry03.set_short_name ('d');
	entry03.set_long_name ("dot");
	entry03.set_description ("Display the disks' object hierarchy");
	add_entry (entry03, dot);

	Glib::OptionEntry entry04;
	entry04.set_short_name ('s');
	entry04.set_long_name ("separate");
	entry04.set_description ("Use separate diagrams for each disk (dot only)");
	add_entry (entry04, separate);

	Glib::OptionEntry entry05;
	entry05.set_short_name ('c');
	entry05.set_long_name ("config");
	entry05.set_description ("Use this file to configure DParted");
	add_entry_filename (entry05, config);

	Glib::OptionEntry entry06;
	entry06.set_short_name ('t');
	entry06.set_long_name ("theme");
	entry06.set_description ("Use this file to style the graphical application");
	add_entry_filename (entry06, theme);

	Glib::OptionEntry entry07;
	entry07.set_short_name ('x');
	entry07.set_long_name ("xcoord");
	entry07.set_description ("X coordinate of the main window (app only)");
	add_entry (entry07, x);

	Glib::OptionEntry entry08;
	entry08.set_short_name ('y');
	entry08.set_long_name ("ycoord");
	entry08.set_description ("Y coordinate of the main window (app only)");
	add_entry (entry08, y);

	Glib::OptionEntry entry09;
	entry09.set_short_name ('w');
	entry09.set_long_name ("width");
	entry09.set_description ("Width of the main window (app only)");
	add_entry (entry09, w);

	Glib::OptionEntry entry10;
	entry10.set_short_name ('h');
	entry10.set_long_name ("height");
	entry10.set_description ("Height of the main window (app only)");
	add_entry (entry10, h);
}

void OptionGroup::on_error (Glib::OptionContext& /* context */, Glib::OptionGroup& /* group */)
{
	std::cout << "on_error called" << std::endl;
}

