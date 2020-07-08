# Building a standalone app from a source code FMU

This project demonstrates how to run an [FMI 2.0](https://fmi-standard.org/) source code FMU as a standalone app.
It consists of a simple C program that creates an instance of the `Heater` model. Its simulation loop turns the power for the `heatingResistor` on and off by setting the input variable `u` to keep the temperature `T` of the `heatCapacitor` at 40 °C.

![Heater.mo](Heater.png)

For each time step the current simulation time, `u` and `T` are displayed on the command line:

```
time, u, T
0.00, 0, -7.15
0.10, 0, 20.72
0.20, 0, 21.43
0.30, 0, 22.14
...
3.40, 0, 39.82
3.50, 1, 40.28
3.60, 1, 40.73
3.70, 1, 40.26
3.80, 0, 39.79
3.90, 0, 39.32
4.00, 0, 39.78
4.10, 1, 40.23
4.20, 1, 40.68
4.30, 1, 40.21
4.40, 0, 39.74
...
```

## Project Structure

- `Heater.mo` - Modelica model of the Heater
- `Heater/` - extracted FMU (exported with Dymola 2021)
- `include/` - FMI headers
- `src/heater.c` - source code of the standalone app
- `CMakeLists.txt` - the CMake project

## Building the Standalone App

### Prerequisites

- clone or download and extract this repository
- install [CMake](https://cmake.org/)
- install a supported toolchain (run `cmake --help` to get a list of all available generators)

### Building on Windows with Visual Studio

- run `cmake -G"Visual Studio 15 2017 Win64" -Bbuild .` to generate a Visual Studio 2017 solution

- open `build/Heater.sln` in Visual Studio 2017

- In the Project Explorer right-click on the `Heater` project and select `Debug > Start new instance` to build and run the app

### Building on Linux with GCC

- run `cmake -Bbuild .` to generate the Unix Makefiles

- run `cmake --build build` to build the app

- run the app with `./build/Heater`

### Exporting the FMU

- in Dymola 2021 click `File > Open > Load...` and select `Heater.mo`

- on the `Simulation` tab open the `Translate` menu and select `FMU`

![Translate FMU](Translate-FMU.png)

- in the `Export FMU` select the following options and click `OK`

![Export FMU](Export-FMU.png)
