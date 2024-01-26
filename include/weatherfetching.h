//
// Created by parakram on 1/26/24.
//

#ifndef WEATHERAPP_INCLUDE_WEATHERFETCHING_H_
#define WEATHERAPP_INCLUDE_WEATHERFETCHING_H_

#include <cpr/cpr.h>
using std::string;

struct weatherData {
  int statusCode;
  string resData;
};

class WeatherFetcher {
 public:
  const string currentBaseURL = "https://api.openweathermap.org/data/2.5/weather?";
  const string forecastBaseURL = "https://api.openweathermap.org/data/2.5/forecast?";
  explicit WeatherFetcher();
  [[nodiscard]] struct weatherData fetchData(const string &reqURL) const;
};

#endif //WEATHERAPP_INCLUDE_WEATHERFETCHING_H_
