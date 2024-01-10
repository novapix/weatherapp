#include "mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include "./ui_mainwindow.h"
#include <cpr/cpr.h>
#include <format>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::fetchWeather() {
  QString cityInput = ui->cityInput->text();
  std::string city = cityInput.toStdString();
  const std::string apiKey = "";
  const std::string baseUrl = "http://api.openweathermap.org/data/2.5/weather?q=";
  std::string apiURL = std::format("{}{}&appid={}", baseUrl, city, apiKey);
  cpr::Response res = cpr::Get(cpr::Url{apiURL});
  if (res.error) {
    if (res.status_code == 404) {
      QMessageBox::warning(this, "Error", "City not Found");
    }
    QMessageBox::warning(this, "Error", "failed to fetch weather data");
  }
  QJsonDocument jsonRes = QJsonDocument::fromJson(res.text.c_str());
}
