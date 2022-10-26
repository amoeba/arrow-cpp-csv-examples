all: table_reader_example streaming_reader_example streaming_reader_type_error_example

table_reader_example: table_reader_example.cc
	$(CXX) -o $@ $(CXXFLAGS) --std=c++11 $< $$(pkg-config --cflags --libs arrow)

streaming_reader_example: streaming_reader_example.cc
	$(CXX) -o $@ $(CXXFLAGS) --std=c++11 $< $$(pkg-config --cflags --libs arrow)

streaming_reader_type_error_example: streaming_reader_type_error_example.cc
	$(CXX) -o $@ $(CXXFLAGS) --std=c++11 $< $$(pkg-config --cflags --libs arrow)
