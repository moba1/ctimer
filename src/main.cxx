#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <exception>

void
timer(unsigned long long time) {
  for (;time > 0; time--) {
    std::cout << "\r\033[2K" << time << " [sec]" << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "\r\033[2K" << "finish!" << std::endl;
}

void
usage(const char *program_path) {
  const auto program_name = std::filesystem::path(program_path)
      .filename()
      .generic_string();

  std::cout
    << "command line timer"              << std::endl
    << std::endl
    << "Usage:"                          << std::endl
    << "  " << program_name << " <time>" << std::endl
    << "  " << program_name << " -h"     << std::endl
    << "  " << program_name << " -v"     << std::endl
    << std::endl
    << "Arguments:"                      << std::endl
    << "  <time>"                        << std::endl
    << "    end time [sec]"              << std::endl
    << std::endl
    << "Options"                         << std::endl
    << "  -h"                            << std::endl
    << "    show help"                   << std::endl
    << "  -v"                            << std::endl
    << "    show version"                << std::endl;
}

const auto VERSION = "1.0";
void
version(void) {
  std::cout << "version: " << VERSION << std::endl;
}

int
main(int argc, char *argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "hv")) != -1) {
    switch (opt) {
      case 'h':
        usage(argv[0]);
        return 0;
      case 'v':
        version();
        return 0;
      default:
        return 1;
    }
  }
  if (argc - optind < 1) {
    std::cerr << "<time> required" << std::endl;
    return 1;
  }

  try {
    const auto time = std::stoull(argv[optind]);
    timer(time);
  } catch (const std::invalid_argument& e) {
    std::cerr << "<time> must be non-negative integer" << std::endl;
    return 1;
  } catch (const std::out_of_range& e) {
    std::cerr << "<time> is larger than max";
    return 1;
  }

  return 0;
}
