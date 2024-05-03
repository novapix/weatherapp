#include "../include/mainwindow.h"
#include "../include/apichecker.h"
#include "../include/geocoding.h"
#include <QMessageBox>
#include "../include/ui_mainwindow.h"
#include <optional>
#include <format>
#include <QDir>
#include <QPixmap>

using std::string;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("Weather App");
  QIcon icon(":/resource/assets/icon.png");  // Using the /resource prefix
  if (icon.isNull()) {
	qDebug() << "Error: Failed to load window icon!";
  } else {
	setWindowIcon(icon);
  }
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
  resData res = WeatherFetcher::fetchData(reqURL);
  if (res.statusCode != 200) {
	if (res.statusCode == 404) {
	  QMessageBox::warning(this, "Error", "City not Found");
	} else {
	  QMessageBox::warning(this, "Error", "failed to fetch weather data");
	}
  }
  std::optional<weatherData> data = WeatherFetcher::parseWeather(res.resText);
  if (data) {
	updateWeather(data.value());
  } else {
	QMessageBox::warning(this, "Error", "Invalid JSON document.");
  }
}

void MainWindow::updateWeather(const weatherData &wData) {
  ui->presentLabel->setText(QString("Current Weather"));
//  ui->tempDetailsText->setAlignment(Qt::AlignCenter);
  QString tempDetailsText;
  QTextStream tempDetailsStream(&tempDetailsText);

  tempDetailsStream << "Temperature: " << wData.temperature << " °C" << Qt::endl
					<< "Max Temp: " << wData.temperatureMax << " °C" << Qt::endl
					<< "Min Temp: " << wData.temperatureMin << " °C" << Qt::endl
					<< "Humidity: " << wData.humidity << "%";

  ui->tempDetails->setText(tempDetailsText);
  ui->presentIcon->setPixmap(QPixmap(std::format(":/icons/assets/wicons/{}", wData.icon).c_str()));
  bool isDay = isDayTime(wData.currentDt, wData.sunriseDT, wData.sunsetDT);
  QString backgroundFile;
  if (isDay) {
	backgroundFile = ":/resource/assets/day.png";
  } else {
	backgroundFile = ":/resource/assets/night.png";
  }
  QPixmap backgroundPixmap(backgroundFile);
  if (backgroundPixmap.isNull()) {
	qDebug() << "Failed to load background image.";
  } else {
	ui->backgroundLabel->setPixmap(backgroundPixmap);
  }
}

void MainWindow::clearResults() {
  ui->backgroundLabel->clear();
  ui->tempDetails->clear();
  ui->presentLabel->clear();
  ui->cityInput->clear();
  ui->presentIcon->clear();
}
bool MainWindow::isDayTime(std::time_t currentTime, std::time_t sunriseTime, std::time_t sunsetTime) {
  return currentTime >= sunriseTime && currentTime <= sunsetTime;
}


