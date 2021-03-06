#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include "window.h"

class Application : public Gtk::Application
{
protected:
	Application();

public:
	static Glib::RefPtr<Application> create();

protected:
	virtual int on_command_line (const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line);

private:
	Window* window = nullptr;

	void create_window (void);
	void show_window (void);

	void on_window_hide (Gtk::Window* window);
};

#endif // _APPLICATION_H_

