#include <iostream>
#include <string>

#include <gtkmm/box.h>
#include <gtkmm/label.h>

#include "window.h"

Window::Window()
{
	box.set_orientation (Gtk::ORIENTATION_VERTICAL);
	add (box);
}

void Window::display_info (const char* key, const std::string& value)
{
	std::string k (key);
	Gtk::Label* l = Gtk::manage (new Gtk::Label (k + ": " + value));

	box.pack_start (*l, false, false);

	show_all_children();
}

void Window::load_config (const std::string& filename)
{
	display_info ("config", filename);
}

void Window::load_theme (const std::string& filename)
{
	display_info ("theme", filename);
}

void Window::load_disk (const std::string& filename)
{
	display_info ("disk", filename);
}

void Window::set_geometry (int x, int y, int w, int h)
{
	x = std::max (x, 0);
	y = std::max (y, 0);

	w = std::max (w, 100);
	h = std::max (h, 100);

	move (x, y);
	resize (w, h);
}

