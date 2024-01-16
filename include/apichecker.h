#ifndef WEATHERAPP_INCLUDE_APICHECKER_H_
#define WEATHERAPP_INCLUDE_APICHECKER_H_

#include <cpr/cpr.h>
#include <QMainWindow>
#include <QPushButton>

using std::string;

class ApiCheck {
 private:
  const string configLocation = "apikey.txt";
 public:
  explicit ApiCheck();
  void checkFileExists();
};

#endif //WEATHERAPP_INCLUDE_APICHECKER_H_
