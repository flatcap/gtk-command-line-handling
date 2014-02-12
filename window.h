#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>

#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>

class Window : public Gtk::ApplicationWindow
{
public:
	Window();

	void load_config (const std::string& filename);
	void load_theme  (const std::string& filename);
	void load_disk   (const std::string& filename);

protected:
	Gtk::Box box;

	void display_info (const char* key, const std::string& value);
};

#endif // _WINDOW_H_

