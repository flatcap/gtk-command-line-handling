#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>

#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>

class Window : public Gtk::ApplicationWindow
{
public:
	Window();

	bool load_file (const std::string& filename);

protected:
	Gtk::Box box;
};

#endif // _WINDOW_H_

