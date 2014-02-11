#include <iostream>

#include "window.h"

Window::Window()
{
	add (box);
}

bool Window::load_file (const std::string& filename)
{
	if (filename.empty())
		return false;

	Gtk::Label* l = Gtk::manage (new Gtk::Label (filename));

	box.pack_end (*l, false, false);

	show_all_children();
	return true;
}

