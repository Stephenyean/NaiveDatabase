SQL Parser (C++)
==========

This is a SQL Parser for C++. It parses the given SQL query into C++ objects.
It is developed for integration in hyrise (https://github.com/hyrise/hyrise).


## Usage

**Prerequisites:**
* bison (https://www.gnu.org/software/bison/)
* flex (http://flex.sourceforge.net/)

To create the full parser code run `make build`. The parser library code is created in `build/`.

To use the SQL Parser in your own code, you only need to include `SQLParser.h` and build+link all the source files from the parser with your project.


