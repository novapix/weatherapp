//
// Created by parakram on 1/26/24.
//
#include "../include/weatherfetching.h"

WeatherFetcher::WeatherFetcher() = default;

struct weatherData WeatherFetcher::fetchData(const std::string &reqURL) const {
  cpr::Response res = cpr::Get(cpr::Url{reqURL});
  return {static_cast<int>(res.status_code), res.text};
}
