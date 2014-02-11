#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <gtkmm.h>

class Window : public Gtk::ApplicationWindow
{
public:
	//We do not take the file as a constructor parameter,
	//so we can separate window creation and hiding of the window
	//when loading fails.
	explicit Window();

	bool load_file (const Glib::RefPtr<Gio::File>& file);

private:
	Gtk::ScrolledWindow m_scrolledwindow;
	Gtk::TextView m_view;
};

#endif // _WINDOW_H_

