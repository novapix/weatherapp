#include "../include/mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include "../include/ui_mainwindow.h"
#include <format>

using std::string;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->btnFetch, &QPushButton::clicked, this, &MainWindow::fetchWeather);
  // connect(ui->btnFetch, SIGNAL(returnPressed()), this, &MainWindow::fetchWeather);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::fetchWeather() {
  QString cityInput = ui->cityInput->text();
  string city = cityInput.toStdString();
  const string apiKey = "x";
  if (apiKey.empty()) {
    QMessageBox::warning(this, "API ERROR", "Please Add API KEY");
  } else {
    const string baseUrl = "https://api.openweathermap.org/data/2.5/weather?q=";
    string reqURL = std::format("{}{}&appid={}", baseUrl, city, apiKey);
    cpr::Response res = cpr::Get(cpr::Url{reqURL});
    if (res.status_code == 404) {
      QMessageBox::warning(this, "Error", "City not Found");
    }
    if (res.status_code != 200) {
      QMessageBox::warning(this, "Error", "failed to fetch weather data");
    }
    QJsonDocument jsonResponse = QJsonDocument::fromJson(res.text.c_str());
    if (jsonResponse.isObject()) {
      // Get the "main" object and extract the temperature, using 0.0 as a default
      // if "temp" is not present
      double temperature = jsonResponse.object()["main"].toObject()["temp"].toDouble() - 273.15;
      double maxTemp = jsonResponse.object()["main"].toObject()["temp_max"].toDouble() - 273.15;
      double minTemp = jsonResponse.object()["main"].toObject()["temp_min"].toDouble() - 273.15;


      ui->tempDetailsText->setText(QString("Temperature: %1 °C\n"
			    "Max Temp: %2 °C\n"
			    "Min Temp: %3 °C")
			.arg(temperature)
			.arg(maxTemp)
			.arg(minTemp));
    } else {
      QMessageBox::warning(this, "Error", "Invalid JSON document.");
    }
  }
}