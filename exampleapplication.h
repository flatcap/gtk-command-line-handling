#ifndef _EXAMPLEAPPLICATION_H_
#define _EXAMPLEAPPLICATION_H_

#include <gtkmm.h>

class ExampleApplication : public Gtk::Application
{
protected:
	ExampleApplication();

public:
	static Glib::RefPtr<ExampleApplication> create();

protected:
	virtual void on_activate();
	virtual void on_open (const Gio::Application::type_vec_files& files, const Glib::ustring& hint);
	virtual int on_command_line (const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line);

private:
	void create_window (const Glib::RefPtr<Gio::File>& file = Glib::RefPtr<Gio::File>());

	void on_window_hide (Gtk::Window* window);
};

#endif // _EXAMPLEAPPLICATION_H_

