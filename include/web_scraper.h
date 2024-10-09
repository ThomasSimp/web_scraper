#ifndef WEBSCRAPER_H
#define WEBSCRAPER_H

#include <gtk/gtk.h>
#include <string>

/**
 * @class WebScraper
 * @brief A class that represents a web scraping application with a graphical user interface (GUI).
 *
 * The WebScraper class provides functionality to scrape content from web pages specified by the user
 * through a URL input. It utilizes the GTK+ library to create a user-friendly interface that allows
 * users to input a URL, initiate the scraping process, and view the results directly within the application.
 *
 * This class is designed to encapsulate all the necessary components for the web scraping
 * functionality, including user interface elements and the web scraping logic.
 */
class WebScraper {
public:
    /**
     * @brief Default constructor for the WebScraper class.
     *
     * Initializes the main window and its components. This constructor sets up the GTK+ environment
     * and creates the necessary widgets for user interaction.
     */
    WebScraper(); // Constructor

    /**
     * @brief Displays the main window of the application.
     *
     * This method is responsible for showing the main application window to the user.
     * It also sets up the layout and connects the necessary signals to their respective callback functions.
     */
    void show(); // Show the main window

    /**
     * @brief Callback function that is triggered when the scrape button is clicked.
     *
     * This static method is connected to the 'clicked' signal of the scrape button. It
     * retrieves the URL entered by the user and initiates the web scraping process by calling
     * the scrape method. The results are then displayed in the result view.
     *
     * @param widget The GtkWidget that was clicked (the scrape button).
     * @param data User data passed to the callback (usually a pointer to the WebScraper instance).
     */
    static void on_scrape_clicked(GtkWidget *widget, gpointer data); // Callback for the button click

    /**
     * @brief Performs the web scraping operation for the specified URL.
     *
     * This method takes a URL as input, performs the scraping operation, and retrieves the content
     * from the web page. The content is then processed and returned as a string.
     *
     * @param url The URL of the web page to scrape.
     * @return A string containing the scraped content from the web page.
     */
    std::string scrape(const gchar *url); // Function to perform the web scraping

private:
    GtkWidget *window;       ///< Main application window.
    GtkWidget *url_entry;    ///< Entry field for the user to input the URL to scrape.
    GtkWidget *scrape_button; ///< Button that initiates the scraping process when clicked.
    GtkWidget *result_view;   ///< Text view widget to display the results of the web scraping.
    GtkWidget *vbox;          ///< Vertical box layout to arrange the widgets vertically.
    GtkWidget *footer_box;    ///< Footer box for additional items (e.g., status messages, credits).
};

#endif // WEBSCRAPER_H
