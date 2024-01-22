#include "../include/mainwindow.h"
#include "../include/apichecker.h"
#include "../include/geocoding.h"
#include <QJsonDocument>
#include <QMessageBox>
#include "../include/ui_mainwindow.h"
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
  cpr::Response res = cpr::Get(cpr::Url{reqURL});
  qDebug() << res.text;
  if (res.status_code != 200) {
	if (res.status_code == 404) {
	  QMessageBox::warning(this, "Error", "City not Found");
	} else {
	  QMessageBox::warning(this, "Error", "failed to fetch weather data");
	}
  }
  QJsonDocument jsonResponse = QJsonDocument::fromJson(res.text.c_str());
  if (jsonResponse.isObject()) {
	QString assetsPath = QCoreApplication::applicationDirPath() + "/../assets";
	qDebug() << assetsPath;
	QString backgroundImage = QDir(assetsPath).filePath("day.png");
	QPixmap backgroundPixmap(backgroundImage);
	qDebug() << "Resource Prefix:" << QCoreApplication::applicationDirPath();

	if (backgroundPixmap.isNull()) {
	  qDebug() << "Failed to load background image.";
	} else {
	  ui->backgroundLabel->setPixmap(backgroundPixmap);
	}

	updateWeather(jsonResponse);
  } else {
	QMessageBox::warning(this, "Error", "Invalid JSON document.");
  }
}

void MainWindow::updateWeather(const QJsonDocument &jsonRes) {
  // Get the "main" object and extract the temperature, using 0.0 as a default
  // if "temp" is not present
  double temperature = jsonRes.object()["main"].toObject()["temp"].toDouble() - 273.15;
  double maxTemp = jsonRes.object()["main"].toObject()["temp_max"].toDouble() - 273.15;
  double minTemp = jsonRes.object()["main"].toObject()["temp_min"].toDouble() - 273.15;
  ui->presentLabel->setText(QString("Current Weather"));
//  ui->tempDetailsText->setAlignment(Qt::AlignCenter);
  ui->tempDetailsText->setText(QString("Temperature: %1 °C\n"
									   "Max Temp: %2 °C\n"
									   "Min Temp: %3 °C")
								   .arg(temperature)
								   .arg(maxTemp)
								   .arg(minTemp));

}
void MainWindow::clearResults() {
  ui->backgroundLabel->clear();
  ui->tempDetailsText->clear();
  ui->presentLabel->clear();
  ui->cityInput->clear();
}

