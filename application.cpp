#include <iostream>

#include "application.h"
#include "window.h"
#include "optiongroup.h"

Application::Application() :
	Gtk::Application ("org.gtkmm.examples.application",
	Gio::ApplicationFlags (Gio::APPLICATION_HANDLES_OPEN | Gio::APPLICATION_HANDLES_COMMAND_LINE))
{
	Glib::set_application_name ("Gtk::Application Example");
}

Glib::RefPtr<Application> Application::create()
{
	return Glib::RefPtr<Application> (new Application());
}

void Application::create_window (const Glib::RefPtr<Gio::File>& file)
{
	Window* window = new Window();

	//Make sure that the application runs for as long this window is still open:
	add_window (*window);

	//Delete the window when it is hidden.
	//That's enough for this simple example.
	window->signal_hide().connect (sigc::bind<Gtk::Window*> (sigc::mem_fun (*this, &Application::on_window_hide), window));

	window->show();

	if (!file) {
		//This is probably an new empty file, as a result of an activation rather
		//than an open.
		return;
	}

	const bool loaded = window->load_file (file);
	if (!loaded)
		std::cerr << "This file could not be loaded: " << file->get_path() << std::endl;
}

void Application::on_window_hide (Gtk::Window* window)
{
	delete window;
}

void Application::on_activate()
{
	//std::cout << "debug1: " << G_STRFUNC << std::endl;
	// The application has been started, so let's show a window.
	// A real application might want to reuse this "empty" window in on_open(),
	// when asked to open a file, if no changes have been made yet.
	create_window();
}

void Application::on_open (const Gio::Application::type_vec_files& files, const Glib::ustring& hint)
{
	// The application has been asked to open some files,
	// so let's open a new window for each one.
	//std::cout << "debug: files.size()=" << files.size() << std::endl;
	for (guint i = 0; i < files.size(); i++) {
		Glib::RefPtr<Gio::File> file = files[0];
		if (!file) {
			std::cerr << G_STRFUNC << ": file is null." << std::endl;
		} else {
			create_window (file);
		}
	}

	//Call the base class's implementation:
	Gtk::Application::on_open (files, hint);
}

int Application::on_command_line (const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line)
{
	//Parse command-line arguments that were passed either to the main (first) instance
	//or to subsequent instances.
	//Note that this parsing is happening in the main (not remote) instance.
	int argc = 0;
	char** argv = command_line->get_arguments (argc);

	Glib::OptionContext context;
	OptionGroup group;
	context.set_main_group (group);
	context.set_summary ("My summary text");
	context.set_description ("My descriptive text");

	try {
		context.parse (argc, argv);
	} catch (const Glib::Error& ex) {
		std::cerr << "Exception parsing command-line: " << ex.what() << std::endl;
		std::cerr << context.get_help() << std::endl;
		return EXIT_FAILURE;
	}

	// The GOption documentation says that options without names will be returned
	// to the application as "rest arguments", meaning they will be left in the argv.
	std::string filepath;
	if (argc > 1) {
		const char* pch = argv[1];
		if (pch) {
			filepath = pch;
		}
	}

	if (filepath.empty()) {
		//Open a new "document" instead:
		activate();
		return EXIT_FAILURE;
	}

	std::cout << "debug: parsed values: " << std::endl <<
		"	 foo = " << group.m_arg_foo << std::endl <<
		"	 goo = " << group.m_arg_goo << std::endl <<
		"	 filepath = " << filepath << std::endl;

	Glib::RefPtr<Gio::File> file = Gio::File::create_for_path (filepath);
	open (file);

	//The local instance will eventually exit with this status code:
	return EXIT_SUCCESS;
}

