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
	// DO SOMETHING TO VALIDATE API KEY
//	validateAPIKey();
  }
}

void ApiCheck::takeAPIInput() const {
  bool validInput = false;
  string apiKey;
  do {
	QString api = QInputDialog::getText(nullptr, "Enter API Key", "Please Enter Your API key");
	apiKey = api.toStdString();

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

bool ApiCheck::validateAPIKey(std::string &apiKey) const {
  cpr::Response res = cpr::Get(cpr::Url{});
  return res.status_code == 200;
}