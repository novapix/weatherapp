//
// Created by parakram on 1/26/24.
//

#ifndef WEATHERAPP_INCLUDE_WEATHERFETCHING_H_
#define WEATHERAPP_INCLUDE_WEATHERFETCHING_H_

#include <cpr/cpr.h>
#include <optional>
#define NUMBER_OF_FORECAST 3
using std::string;

typedef struct responseData {
  int statusCode;
  string resText;
} resData;

typedef struct wData {
  float temperature, temperatureMin, temperatureMax;
  float humidity;
  unsigned int sunriseDT, sunsetDT, currentDt;
  string icon;
} weatherData;

typedef struct fData {
  weatherData forecast[NUMBER_OF_FORECAST];
} forecastData;

class WeatherFetcher {
 public:
  const string currentBaseURL = "https://api.openweathermap.org/data/2.5/weather?";
  const string forecastBaseURL = "https://api.openweathermap.org/data/2.5/forecast?";
  explicit WeatherFetcher();
  [[nodiscard]] static resData fetchData(const string &reqURL);
  [[nodiscard]] static std::optional<weatherData> parseWeather(const string &resText);
};

#endif //WEATHERAPP_INCLUDE_WEATHERFETCHING_H_
