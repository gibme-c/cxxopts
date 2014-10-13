/*

Copyright (c) 2014 Jarryd Beck

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <iostream>

#include "cxxopts.hpp"

int main(int argc, char* argv[])
{
  try
  {

    cxxopts::Options options;

    options.add_options()
      ("a,apple", "an apple")
      ("b,bob", "Bob")
      ("f,file", "File", cxxopts::value<std::vector<std::string>>())
      ("positional", 
        "Positional arguments: these are the arguments that are entered "
        "without an option", cxxopts::value<std::string>())
      ("long-description",
        "thisisareallylongwordthattakesupthewholelineandcannotbebrokenataspace")
      ("help", "Print help")
      ("int", "An integer", cxxopts::value<int>())
      ("option_that_is_too_long_for_the_help", "A very long option")
    ;

    options.parse_positional("positional");

    options.parse(argc, argv);

    if (options.count("a"))
    {
      std::cout << "Saw option ‘a’" << std::endl;
    }

    if (options.count("b"))
    {
      std::cout << "Saw option ‘b’" << std::endl;
    }

    if (options.count("f"))
    {
      auto& ff = options["f"].as<std::vector<std::string>>();
      std::cout << "Files" << std::endl;
      for (const auto& f : ff)
      {
        std::cout << f << std::endl;
      }
    }

    if (options.count("help"))
    {
      std::cout << options.help() << std::endl;
    }

    if (options.count("positional"))
    {
      std::cout << "Positional = " << options["positional"].as<std::string>()
        << std::endl;
    }

    if (options.count("int"))
    {
      std::cout << "int = " << options["int"].as<int>() << std::endl;
    }

    std::cout << "Arguments remain = " << argc << std::endl;

  } catch (const cxxopts::OptionException& e)
  {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }

  return 0;
}