#include <memory>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <parquet/arrow/reader.h>
#include "arrow/csv/api.h"

int main()
{
    std::__fs::filesystem::path filePath = "./data/mtcars.csv";

    arrow::io::IOContext io_context = arrow::io::default_io_context();
    arrow::MemoryPool *pool = arrow::default_memory_pool();
    std::shared_ptr<arrow::io::ReadableFile> infile;
    PARQUET_ASSIGN_OR_THROW(infile, arrow::io::ReadableFile::Open(filePath, pool));

    std::shared_ptr<arrow::io::InputStream> input = infile;

    auto read_options = arrow::csv::ReadOptions::Defaults();
    auto parse_options = arrow::csv::ParseOptions::Defaults();
    auto convert_options = arrow::csv::ConvertOptions::Defaults();

    auto maybe_reader =
        arrow::csv::TableReader::Make(io_context,
                                      input,
                                      read_options,
                                      parse_options,
                                      convert_options);
    if (!maybe_reader.ok()) {
        std::printf(
            "Failed to instantiate arrow::csv::TableReader for %s. Exiting.",
            filePath.c_str()
        );

        return -1;
    }

    std::shared_ptr<arrow::csv::TableReader> reader = *maybe_reader;

    // Read table from CSV file
    auto maybe_table = reader->Read();

    if (!maybe_table.ok()) {
        std::cout << "CSV read error. Exiting.";

        return -1;
    }

    std::shared_ptr<arrow::Table> table = *maybe_table;

    // Print the string representation of the table (schema followed by
    // array data)
    std::cout << table->ToString();
}
