# README — Word Frequency Count (C++)

## Overview

This project reads a text file, counts how many times each unique word appears, and outputs the results sorted by frequency or alphabetically. It also allows you to **edit the text before analysis** and uses **auto-complete** and **auto-correct** features to enhance input accuracy. This makes it useful for text analysis, keyword extraction, or simple natural language processing tasks.

## Features

* Reads any plain text file.
* Edit the text before running the analysis.
* Auto-complete suggestions while editing.
* Auto-correct common typing errors.
* Removes punctuation and normalizes word case (e.g., “Hello” and “hello” are treated the same).
* Counts the frequency of each unique word.
* Outputs results sorted by:

  * **Frequency** (descending) — most common words first.
  * **Alphabetical order** (optional).
* Saves results to a file or displays them on the console.

## Requirements

* C++11 or higher compiler (e.g., `g++`).
* Standard C++ library only — no external dependencies.

## Compilation

```bash
g++ -O2 -std=c++11 -o word_frequency main.cpp
```

(Replace `main.cpp` with your actual file name.)

## Usage

```bash
./word_frequency input.txt output.txt
```

* **input.txt**: Path to the text file you want to analyze (can be edited before processing).
* **output.txt**: Path where results will be saved (optional; if not provided, results are printed to the console).

## Output Format

Example:

```
the: 15
and: 12
to: 8
of: 8
a: 7
```

## Example

**input.txt**:

```
Hello world! Hello ChatGPT.
This world is amazing.
```

**Output**:

```
hello: 2
world: 2
chatgpt: 1
this: 1
is: 1
amazing: 1
```

## Notes

* Words are case-insensitive.
* Punctuation is ignored.
* You can modify the sorting order in the code by changing the comparator function.
* Auto-complete and auto-correct are applied before word counting.

## Future Improvements

* Support for stop-word removal.
* Option to handle very large files using streaming.
* Add CSV/JSON export format.
