#ifndef _EXAMPLEWINDOW_H_
#define _EXAMPLEWINDOW_H_

#include <gtkmm.h>

class ExampleWindow : public Gtk::ApplicationWindow
{
public:
	//We do not take the file as a constructor parameter,
	//so we can separate window creation and hiding of the window
	//when loading fails.
	explicit ExampleWindow();

	bool load_file (const Glib::RefPtr<Gio::File>& file);

private:
	Gtk::ScrolledWindow m_scrolledwindow;
	Gtk::TextView m_view;
};

#endif // _EXAMPLEWINDOW_H_

