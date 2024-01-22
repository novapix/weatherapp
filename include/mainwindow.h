// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <cpr/cpr.h> // Include the libcpr header

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void fetchWeather();

 private:
  Ui::MainWindow *ui;
  // QLineEdit *tempOutput;
  std::string apiKey;
  void updateWeather(const QJsonDocument &jsonRes);
  void clearResults();
};

#endif // MAINWINDOW_H
