#include <iostream>       // For input/output streams: std::cout, std::cerr
#include "grep.h"          // Custom header for Grep class (handles search functionality)
#include "args.h"          // Custom header for ArgParser class (command-line argument parsing)

int main (int argc, char* argv[]) {
    // argc = number of command-line arguments
    // argv = array of argument strings

    args::ArgParser cli;  // Create an instance of ArgParser to handle CLI input
    Grep grep;            // Create an instance of Grep to perform searching

    // Define command-line options for the program
    cli.option("out o", "grep.txt");         // --out or -o : specify output file (default: grep.txt)
    cli.option("pattern r", "");             // --pattern or -r : specify regex pattern (default: empty)
    cli.flag("case-sensitive i");            // --case-sensitive or -i : boolean flag to match case

    cli.parse(argc, argv);                    // Parse the command-line arguments

    auto size = cli.args.size();             // Number of non-option (positional) arguments provided

    // Map command-line options to Grep object
    // Note: Here the flag "i" is actually enabling case-sensitive (code logic could be clearer)
    if (cli.found("i"))
        grep.case_sensitive = true;          // Enable case-sensitive search if -i flag is set

    if (cli.found("o"))
        grep.path = cli.value("out");        // If -o is provided, set output file path

    if (cli.found("r"))
        grep.pattern = cli.value("r");       // If -r is provided, set regex search pattern

    // Handle positional arguments
    if (size == 1)                           // If 1 positional argument: assume it's the file path
        grep.path = cli.args[0];
    else if (size == 2) {                     // If 2 positional arguments: first is word/pattern, second is file path
        grep.word = cli.args[0];             // Store the word to search
        grep.path = cli.args[1];             // Store file path
        grep.pattern = cli.args[0];          // Also set pattern to the word
    } else {
        std::cerr << "not enough arguments supplied" << '\n';  // Warn if insufficient args
    }

    // Run the grep search
    if (grep.run()) {                          // Returns true if search successful
        for (auto &line : grep.lines_found) { // Iterate through all lines found
            if (cli.found("o"))               // If output file flag is set
                grep.write_to_file(line);     // Write line to file
            else 
                std::cout << line << '\n';    // Otherwise, print line to console
        }
    } else {
        std::cerr << "An error has occured parsing file!" << '\n';  // Error message if grep.run() fails
    }
}
