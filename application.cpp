#include <iostream>

#include <glibmm/miscutils.h>
#include <glibmm/optioncontext.h>

#include "application.h"
#include "window.h"
#include "optiongroup.h"

Application::Application() :
	Gtk::Application ("org.gtkmm.examples.application", Gio::ApplicationFlags (Gio::APPLICATION_HANDLES_COMMAND_LINE))
{
	Glib::set_application_name ("command line test");
}

Glib::RefPtr<Application> Application::create()
{
	return Glib::RefPtr<Application> (new Application());
}

void Application::create_window (void)
{
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
	window = nullptr;
}

int Application::on_command_line (const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line)
{
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
	std::cout << "\tapp        = " << group.app        << std::endl;
	std::cout << "\tlist       = " << group.list       << std::endl;
	std::cout << "\tdot        = " << group.dot        << std::endl;
	std::cout << "\tseparate   = " << group.separate   << std::endl;
	std::cout << "\tproperties = " << group.properties << std::endl;
	std::cout << "\tx          = " << group.x          << std::endl;
	std::cout << "\ty          = " << group.y          << std::endl;
	std::cout << "\tw          = " << group.w          << std::endl;
	std::cout << "\th          = " << group.h          << std::endl;

	if (!group.app && !group.list && !group.properties && !group.dot) {
		group.app = true;
	}

	std::cout << "validate options" << std::endl;

	if (group.separate && !group.dot) {
		std::cout << "separate without dot" << std::endl;
	}

	if (!group.app) {
		if (group.theme.size())
			std::cout << "theme without app" << std::endl;
		if ((group.x != -1) || (group.y != -1) || (group.w != -1) || (group.h != -1))
			std::cout << "coords without app" << std::endl;
	}

	bool running = !!window;

	if (group.app) {
		create_window();

		if (group.config.size()) {
			std::cout << "config:" << std::endl;
			for (auto c : group.config) {
				std::cout << '\t' << c << std::endl;
				window->load_config (c);
			}
		}

		if (group.theme.size()) {
			std::cout << "theme:" << std::endl;
			for (auto t : group.theme) {
				std::cout << '\t' << t << std::endl;
				window->load_theme (t);
			}
		}

		if ((group.x > -1) || (group.y > -1) || (group.w > -1) || (group.h > -1)) {
			window->set_geometry (group.x, group.y, group.w, group.h);
		}
	}

	if (disks.size()) {
		std::cout << "scan only: ";
		for (auto d : disks) {
			std::cout << "\"" << d << "\" ";
			if (window) {
				window->load_disk (d);
			}
		}
		std::cout << std::endl;
	} else {
		if (!running) {
			std::cout << "scan all disks" << std::endl;
		}
	}

	if (group.list) {
		std::cout << "list objects" << std::endl;
	}

	if (group.properties) {
		std::cout << "list properties" << std::endl;
	}

	if (group.dot) {
		if (group.separate) {
			std::cout << "dot (separate)" << std::endl;
		} else {
			std::cout << "dot (single)" << std::endl;
		}
	}

	if (running) {
		std::cout << "we're already active" << std::endl;
		create_window();
	}

	return EXIT_SUCCESS;
}

