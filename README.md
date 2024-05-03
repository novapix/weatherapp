# Weather App

A cross-platform desktop application that provides current weather information for a specified location.

## Project Overview

This weather app was created as part of the curriculum for the CSIT (3rd semester) at Kathford College of Engineering
and Management.
The goal of the project was to develop a desktop application using C++ and the Qt framework.

## Features

- Get current weather conditions for a location by entering city name or coordinates
- Display weather information such as temperature, humidity, wind speed, and weather description
- Switch between day and night background themes based on the sunrise and sunset times
- Fetch weather data from the OpenWeatherMap API

## Technologies Used

- **Programming Language**: C++
- **GUI Framework**: Qt
- **HTTP Client Library**: [libcpr](https://github.com/libcpr/cpr)
- **Build System**: CMake
- **Package Manager**: vcpkg (for managing dependencies)

## Development Tools

- **IDE**: CLion, Qt Creator
- **UI Designer**: Qt Designer

## Getting Started

### Prerequisites

- C++ compiler (e.g., GCC, Clang, MSVC)
- Qt framework (version 6)
- CMake
- vcpkg (for installing libcpr)

### Building and Running

1. Clone the repository:

```shell
git clone https://github.com/novapix/weatherapp.git
```

2. Install `libcpr` using vcpkg: `vcpkg install cpr`
3. Configure the `CMakeLists.txt` as per requirements.
4. Open the Project in CLion or Qt Creator

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a
pull request.

## License

This project is licensed under the [MIT License](LICENSE).
