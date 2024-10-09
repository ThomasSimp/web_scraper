#include <gtk/gtk.h>
#include "web_scraper.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create and show the main window
    WebScraper *scraper = new WebScraper();
    scraper->show();

    gtk_main();
    return 0;
}
