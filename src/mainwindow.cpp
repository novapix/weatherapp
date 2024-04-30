#include "../include/mainwindow.h"
#include "../include/apichecker.h"
#include "../include/geocoding.h"
#include <QJsonDocument>
#include <QMessageBox>
#include "../include/ui_mainwindow.h"
#include <optional>
#include <format>
#include <QDir>
#include <QPixmap>

using std::string;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->backgroundLabel->setGeometry(0, 0, width(), height());
  ui->backgroundLabel->setScaledContents(true); // Scale background to QLabel Size
  ui->backgroundLabel->lower(); // Lowers the QLabel in the stacking order
  auto *a = new ApiCheck;
  apiKey = a->readApiKeyFromFile();
  delete a;
  connect(ui->btnFetch, &QPushButton::clicked, this, &MainWindow::fetchWeather);
  connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::clearResults);
  // connect(ui->btnFetch, SIGNAL(returnPressed()), this, &MainWindow::fetchWeather);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::fetchWeather() {
  QString cityInput = ui->cityInput->text();
  const string baseURL = "https://api.openweathermap.org/data/2.5/weather?";
  string reqURL;
  if (cityInput.isEmpty()) {
	struct geoData data = geoCoding::workersAPI();
	if (data.latitude > 90 || data.longitude > 180) {
	  QMessageBox::warning(this, "Error", "Unable to get geo coordinates");
	}
	reqURL = std::format("{}lat={}&lon={}&appid={}", baseURL, data.latitude, data.longitude, apiKey);
  } else {
	reqURL = std::format("{}q={}&appid={}", baseURL, cpr::util::urlEncode(cityInput.toStdString()), apiKey);
  }
  qDebug() << reqURL;
  resData res = WeatherFetcher::fetchData(reqURL);
  qDebug() << res.resText;
  if (res.statusCode != 200) {
	if (res.statusCode == 404) {
	  QMessageBox::warning(this, "Error", "City not Found");
	} else {
	  QMessageBox::warning(this, "Error", "failed to fetch weather data");
	}
  }
  std::optional<weatherData> wdata = WeatherFetcher::parseWeather(res.resText);
  if (wdata) {
	weatherData data = wdata.value();
	updateWeather(data);

  } else {
	QMessageBox::warning(this, "Error", "Invalid JSON document.");
  }
}

void MainWindow::updateWeather(const weatherData &wData) {
  // Get the "main" object and extract the temperature, using 0.0 as a default
  // if "temp" is not present

  ui->presentLabel->setText(QString("Current Weather"));
//  ui->tempDetailsText->setAlignment(Qt::AlignCenter);
  ui->tempDetails->setText(QString("Temperature: %1 °C\n"
								   "Max Temp: %2 °C\n"
								   "Min Temp: %3 °C")
							   .arg(wData.temperature)
							   .arg(wData.temperatureMax)
							   .arg(wData.temparatureMin));

}
void MainWindow::clearResults() {
  ui->backgroundLabel->clear();
  ui->tempDetails->clear();
  ui->presentLabel->clear();
  ui->cityInput->clear();
}

