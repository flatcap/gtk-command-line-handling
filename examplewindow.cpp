#include <iostream>

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
{
	set_title ("Gtk::Application example");

	add (m_scrolledwindow);
	m_scrolledwindow.add (m_view);
}

bool ExampleWindow::load_file (const Glib::RefPtr<Gio::File>& file)
{
	if (!file)
		return false;

	try {
		char* contents = 0;
		gsize length = 0;

		if (file->load_contents (contents, length)) {
			if (contents && length) {
				const Glib::ustring text (contents);
				Glib::RefPtr<Gtk::TextBuffer> buffer = m_view.get_buffer();
				buffer->set_text (text);
			}
			g_free (contents);
		}
	} catch (const Glib::Error& ex) {
		std::cerr << G_STRFUNC << ": exception while opening file: " << file->get_uri() << std::endl <<
			"  exception: " << ex.what() << std::endl;

		//Tell the application that this window can no longer be useful to
		//this application, so it can forget about it. The instance might then exit
		//if this is its last open window.
		//Note that we must be careful that the caller only calls this method _after_
		//calling show(), or this would be useless:
		hide();
		return false;
	}

	show_all_children();
	return true;
}

