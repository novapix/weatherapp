#ifndef WEATHERAPP_INCLUDE_APICHECKER_H_
#define WEATHERAPP_INCLUDE_APICHECKER_H_

#include <cpr/cpr.h>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>

using std::string;

class ApiCheck : public QObject {
 Q_OBJECT
 private:
  string configLocation = "apikey.txt";
 public:
  explicit ApiCheck(QObject *parent = nullptr);
  void checkFileExists() const;
  void takeAPIInput() const;
  bool writeToFile(string &apiKey) const;
  static bool validateAPIKey(string &apiKey);
  string readApiKeyFromFile() const;
//  ~ApiCheck();
};

#endif //WEATHERAPP_INCLUDE_APICHECKER_H_
