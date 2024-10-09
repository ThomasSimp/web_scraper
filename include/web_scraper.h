#ifndef WEBSCRAPER_H
#define WEBSCRAPER_H

#include <gtk/gtk.h>
#include <string>

class WebScraper {
public:
    WebScraper(); // Constructor
    void show(); // Show the main window
    static void on_scrape_clicked(GtkWidget *widget, gpointer data); // Callback for the button click
    std::string scrape(const gchar *url); // Function to perform the web scraping

private:
    GtkWidget *window;       // Main window
    GtkWidget *url_entry;    // Entry for the URL
    GtkWidget *scrape_button; // Button to scrape the website
    GtkWidget *result_view;   // Text view to display the results
    GtkWidget *vbox;          // Vertical box to hold the widgets
    GtkWidget *footer_box;    // Footer box to hold footer items
};

#endif // WEBSCRAPER_H
