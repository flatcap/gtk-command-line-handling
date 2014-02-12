#include <iostream>

#include <glibmm/miscutils.h>
#include <glibmm/optioncontext.h>

#include "application.h"
#include "window.h"
#include "optiongroup.h"

Application::Application() :
	Gtk::Application ("org.gtkmm.examples.application",
	Gio::ApplicationFlags (Gio::APPLICATION_HANDLES_COMMAND_LINE))
{
	Glib::set_application_name ("Gtk::Application Example");
}

Glib::RefPtr<Application> Application::create()
{
	return Glib::RefPtr<Application> (new Application());
}

void Application::create_window (void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	if (!window) {
		window = new Window();

		add_window (*window);

		window->signal_hide().connect (sigc::bind<Gtk::Window*> (sigc::mem_fun (*this, &Application::on_window_hide), window));
		window->show();
	}

	window->present();
}

void Application::on_window_hide (Gtk::Window* window)
{
	delete window;
}

void Application::on_activate()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	create_window();
}

int Application::on_command_line (const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
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

	std::vector<std::string> disks;
	for (; argc > 1; argc--, argv++) {
		disks.push_back (argv[1]);
	}

	std::cout << "values: " << std::endl;
	std::cout << "\tapp      = " << group.app      << std::endl;
	std::cout << "\tlist     = " << group.list     << std::endl;
	std::cout << "\tdot      = " << group.dot      << std::endl;
	std::cout << "\tseparate = " << group.separate << std::endl;
	std::cout << "\tx        = " << group.x        << std::endl;
	std::cout << "\ty        = " << group.y        << std::endl;
	std::cout << "\tw        = " << group.w        << std::endl;
	std::cout << "\th        = " << group.h        << std::endl;

	if (group.config.size()) {
		std::cout << "config:" << std::endl;
		for (auto c : group.config) {
			std::cout << '\t' << c << std::endl;
		}
	}

	if (group.theme.size()) {
		std::cout << "theme:" << std::endl;
		for (auto t : group.theme) {
			std::cout << '\t' << t << std::endl;
		}
	}

	if (disks.size()) {
		std::cout << "disks:" << std::endl;
		for (auto d : disks) {
			std::cout << '\t' << d << std::endl;
		}
	}

	if (!group.app && !group.list && !group.dot) {
		group.app = true;
	}

	if (group.separate && !group.dot) {
		std::cout << "separate without dot" << std::endl;
	}

	std::cout << "validate options" << std::endl;

	if (window) {
		std::cout << "we're already active" << std::endl;
		create_window();
		return EXIT_SUCCESS;
	}

	std::cout << "scan disks" << std::endl;

	if (group.app) {
		create_window();
	}

	return EXIT_SUCCESS;
}

