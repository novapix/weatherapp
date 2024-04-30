//
// Created by parakram on 1/26/24.
//
#include "../include/weatherfetching.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

WeatherFetcher::WeatherFetcher() = default;

resData WeatherFetcher::fetchData(const std::string &reqURL) {
  cpr::Response res = cpr::Get(cpr::Url{reqURL});
  return {static_cast<int>(res.status_code), res.text};
}

std::optional<weatherData> WeatherFetcher::parseWeather(const std::string &resText) {
  QJsonDocument jsonRes = QJsonDocument::fromJson(resText.c_str());
  if (jsonRes.isObject()) {
	float temperature = static_cast<float>(jsonRes.object()["main"].toObject()["temp"].toDouble() - 273.15);
	float maxTemp = static_cast<float>(jsonRes.object()["main"].toObject()["temp_max"].toDouble() - 273.15);
	float minTemp = static_cast<float>(jsonRes.object()["main"].toObject()["temp_min"].toDouble() - 273.15);
	float humidity = static_cast<float>(jsonRes.object()["main"].toObject()["humidity"].toDouble());
	int currentDt = jsonRes.object()["dt"].toInt();
	int sunriseDT = jsonRes.object()["sys"].toObject()["sunrise"].toInt();
	int sunsetDT = jsonRes.object()["sys"].toObject()["sunset"].toInt();
	string icon = jsonRes.object()["weather"].toArray().at(0).toObject()["icon"].toString().toStdString() + ".png";
	weatherData res = {
		temperature, minTemp, maxTemp, humidity,
		sunriseDT, sunsetDT, currentDt,
		icon
	};
	return res;
  } else return std::nullopt;
}
