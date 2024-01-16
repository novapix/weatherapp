#include "../include/apichecker.h"
#include <iostream>
#include <filesystem>
#include <fstream>
using std::string;

ApiCheck::ApiCheck() {
  checkFileExists();
}

void ApiCheck::checkFileExists() {
  std::filesystem::path f{configLocation};

}