#include "web_scraper.h"
#include <curl/curl.h>
#include <json/json.h>
#include <iostream>

// Define the WriteCallback function to handle data received from curl
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Helper function to open a URL (used for GitHub button)
void open_url(const char* url) {
    system((std::string("xdg-open ") + url).c_str());
}

// Static method to handle source button click
static void on_source_button_clicked(GtkWidget *widget, gpointer data) {
    open_url("https://github.com/YourRepo");
}

WebScraper::WebScraper() {
    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Web Scraper");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Create a vertical box to hold the widgets
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create an entry for the URL
    url_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), url_entry, FALSE, FALSE, 0);

    // Create a button to scrape the website
    scrape_button = gtk_button_new_with_label("Scrape");
    g_signal_connect(scrape_button, "clicked", G_CALLBACK(on_scrape_clicked), this);
    gtk_box_pack_start(GTK_BOX(vbox), scrape_button, FALSE, FALSE, 0);

    // Create a scrolled window for the text view
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    // Create a text view to display the result
    result_view = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(scrolled_window), result_view);  // Add text view to scrolled window

    // Add a footer box at the bottom
    footer_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), footer_box, FALSE, FALSE, 0);

    // Add a label to the footer box
    GtkWidget *footer_label = gtk_label_new("GitHub: https://github.com/YourRepo");
    gtk_box_pack_start(GTK_BOX(footer_box), footer_label, FALSE, FALSE, 0);

    // Add a button for source code
    GtkWidget *source_button = gtk_button_new_with_label("Source Code");
    g_signal_connect(source_button, "clicked", G_CALLBACK(on_source_button_clicked), NULL);  // Use static function
    gtk_box_pack_start(GTK_BOX(footer_box), source_button, FALSE, FALSE, 0);

    // Connect the delete event signal to exit the application
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void WebScraper::show() {
    gtk_widget_show_all(window);
}

void WebScraper::on_scrape_clicked(GtkWidget *widget, gpointer data) {
    WebScraper *scraper = static_cast<WebScraper*>(data); // Cast data back to WebScraper
    const gchar *url = gtk_entry_get_text(GTK_ENTRY(scraper->url_entry));
    std::string result = scraper->scrape(url);
    
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(scraper->result_view));
    gtk_text_buffer_set_text(buffer, result.c_str(), -1);
}

std::string WebScraper::scrape(const gchar *url) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return readBuffer;
}
