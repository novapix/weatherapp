#ifndef WEATHERAPP_INCLUDE_APICHECKER_H_
#define WEATHERAPP_INCLUDE_APICHECKER_H_

#include <cpr/cpr.h>

#include <QApplication>
#include <QFile>
#include <QInputDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QTextStream>

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
  [[nodiscard]] string readApiKeyFromFile() const;
  //  ~ApiCheck();
};

#endif  // WEATHERAPP_INCLUDE_APICHECKER_H_
