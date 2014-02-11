#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <gtkmm.h>

class Application : public Gtk::Application
{
protected:
	Application();

public:
	static Glib::RefPtr<Application> create();

protected:
	virtual void on_activate();
	virtual void on_open (const Gio::Application::type_vec_files& files, const Glib::ustring& hint);
	virtual int on_command_line (const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line);

private:
	void create_window (const Glib::RefPtr<Gio::File>& file = Glib::RefPtr<Gio::File>());

	void on_window_hide (Gtk::Window* window);
};

#endif // _APPLICATION_H_

