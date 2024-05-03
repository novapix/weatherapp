#include "../include/apichecker.h"
#include <filesystem>

using std::string;

ApiCheck::ApiCheck(QObject *parent) : QObject(parent) {
  checkFileExists();
}

void ApiCheck::checkFileExists() const {
  std::filesystem::path f{configLocation};
  if (!std::filesystem::exists(f)) {
	takeAPIInput();
  } else {
	string apiKey = readApiKeyFromFile();
	bool valid = validateAPIKey(apiKey);
	if (!valid) { takeAPIInput(); }
  }

}

void ApiCheck::takeAPIInput() const {
  bool validInput = false;
  string apiKey;
  do {
	QString api = QInputDialog::getText(nullptr, "Enter API Key", "Please Enter Your API key",
										QLineEdit::Normal, QString(), &validInput);
	apiKey = api.toStdString();
	if (!validInput) {
	  // User canceled the dialog, exit the loop
	  QMessageBox::critical(nullptr, "Error", "Application Cannot Work Without API KEY. Exiting");
	  exit(1);
//	  break;
	}

	if (!writeToFile(apiKey)) {
	  QMessageBox::critical(nullptr, "Error", "Failed to save API key to file. Exiting.");
	  QApplication::exit(EXIT_FAILURE);
	} else {
	  validInput = validateAPIKey(apiKey);
	  if (!validInput) {
		QMessageBox::critical(nullptr, "Error", "Invalid API key. Please enter a valid key.");
	  }
	}
  } while (!validInput);
}

bool ApiCheck::writeToFile(string &apiKey) const {
  QFile file(configLocation.c_str());
  // open the file for writing in text mode. If the file doesn't exist, it will be created, and if it already exists,
  // its content will be truncated
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
	QTextStream out(&file);
	out << apiKey.c_str();
	file.close();
	return true;
  }
  return false;
}

bool ApiCheck::validateAPIKey(string &apiKey) {
  string reqUrl = std::format("https://api.openweathermap.org/data/2.5/weather?lat=44.34&lon=10.99&appid={}",
							  apiKey);
  cpr::Response res = cpr::Get(cpr::Url{reqUrl});
  return res.status_code == 200;
}

string ApiCheck::readApiKeyFromFile() const {
  QString apiKey;
  QFile file(configLocation.c_str());
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
	QTextStream in(&file);
	apiKey = in.readLine();
	file.close();
  } else {
	QMessageBox::critical(nullptr, "Error", "Failed to read API key to file. Exiting.");
	QApplication::exit(EXIT_FAILURE);
  }

  return apiKey.toStdString();
}