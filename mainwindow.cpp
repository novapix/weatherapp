#include "include/mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include "./include/ui_mainwindow.h"
#include <format>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->btnFetch, &QPushButton::clicked, this, &MainWindow::fetchWeather);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::fetchWeather() {
  QString cityInput = ui->cityInput->text();
  std::string city = cityInput.toStdString();
  const std::string apiKey = "";
  if (apiKey.empty()) {
    QMessageBox::warning(this, "API ERROR", "Please Add API KEY");
  } else {
    const std::string baseUrl = "http://api.openweathermap.org/data/2.5/weather?q=";
    std::string reqURL = std::format("{}{}&appid={}", baseUrl, city, apiKey);
    cpr::Response res = cpr::Get(cpr::Url{reqURL});
    if (res.status_code == 404) {
      QMessageBox::warning(this, "Error", "City not Found");
    }
    if (res.error) {
      QMessageBox::warning(this, "Error", "failed to fetch weather data");
    }
    QJsonDocument jsonResponse = QJsonDocument::fromJson(res.text.c_str());
    if (jsonResponse.isObject()) {
      // Get the "main" object and extract the temperature, using 0.0 as a default
      // if "temp" is not present
      double temperature = jsonResponse.object()["main"].toObject()["temp"].toDouble() - 273.15;

      // Set the temperature in the read-only QLineEdit
      ui->tempOutput->setText(QString("Temperature: %1 °C").arg(temperature));
    } else {
      QMessageBox::warning(this, "Error", "Invalid JSON document.");
    }
  }
}
