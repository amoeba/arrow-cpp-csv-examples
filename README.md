# arrow-cpp-csv-examples

Short demonstrations of using [Arrow](https://arrow.apache.org)'s two methods of reading in CSV file as Arrow Data:

1. [TableReader](https://arrow.apache.org/docs/cpp/api/formats.html#_CPPv4N5arrow3csv11TableReaderE)
2. [StreamingReader](https://arrow.apache.org/docs/cpp/api/formats.html#_CPPv4N5arrow3csv15StreamingReaderE)

Written up mostly as an example for myself but may be useful for others. See the [Arrow C++ docs](https://arrow.apache.org/docs/cpp/csv.html) for more information.

## Running

### Pre-requisites

- `pkg-config` (`brew install pkg-config`)
- A >=C++11 compiler (e.g., clang 14)
- Arrow C++ headers (`brew install apache-arrow`)

## Compile

A `Makefile` is provided to make compiling both examples a single command:

```sh
make
```

## Run

- TableReader:

    ```sh
    ./table_reader_example
    ```
- StreamingReader:

    ```sh
    ./streaming_reader_example
    ```
