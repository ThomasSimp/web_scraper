CXX = g++
CXXFLAGS = `pkg-config --cflags gtk+-3.0` -I./include -I/usr/include/jsoncpp
LDFLAGS = `pkg-config --libs gtk+-3.0` -lcurl -ljsoncpp

# Specify the object files with the src/ prefix
OBJECTS = src/main.o src/web_scraper.o

# Rule to build the executable
web_scraper: $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Rule to compile main.cpp
src/main.o: src/main.cpp include/web_scraper.h
	$(CXX) -c src/main.cpp $(CXXFLAGS) -o src/main.o

# Rule to compile web_scraper.cpp
src/web_scraper.o: src/web_scraper.cpp include/web_scraper.h
	$(CXX) -c src/web_scraper.cpp $(CXXFLAGS) -o src/web_scraper.o

# Rule to clean the build
clean:
	rm -f src/*.o web_scraper
