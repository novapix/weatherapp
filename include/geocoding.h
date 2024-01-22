#ifndef WEATHERAPP_INCLUDE_GEOCODING_H_
#define WEATHERAPP_INCLUDE_GEOCODING_H_

#include <cpr/cpr.h>
#include <QJsonDocument>
#include <QJsonObject>

using std::string;

struct geoData {
  double latitude;
  double longitude;
};

class geoCoding {
 public:
  explicit geoCoding();
  static struct geoData workersAPI();
  static struct geoData backupAPI();
};

#endif //WEATHERAPP_INCLUDE_GEOCODING_H_
