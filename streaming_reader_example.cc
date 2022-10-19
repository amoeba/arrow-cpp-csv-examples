#include <memory>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <arrow/record_batch.h>
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
        arrow::csv::StreamingReader::Make(io_context,
                                          input,
                                          read_options,
                                          parse_options,
                                          convert_options);
    if (!maybe_reader.ok()) {
        std::printf(
            "Failed to instantiate arrow::csv::StreamingReader for %s. Exiting.",
            filePath.c_str()
        );

        return -1;
    }

    std::shared_ptr<arrow::csv::StreamingReader> reader = *maybe_reader;
    std::shared_ptr<arrow::RecordBatch> batch;

    arrow::Status status = reader->ReadNext(&batch);

    if (!status.ok()) {
        std::cout << "Failed to read RecordBatch. Exiting.";

        return -1;
    }

    if (batch == NULL) {
        std::cout << "No more rows to read. Exiting.";

        return 0;
    }

    std::printf("%s\n---\n", reader->schema()->ToString().c_str());

    while (batch != NULL) {
        std::cout << batch->ToString();
        status = reader->ReadNext(&batch);

        if (!status.ok()) {
            std::cout << "Error reading RecordBatch. Exiting";
            return -1;
        }
    }
}
