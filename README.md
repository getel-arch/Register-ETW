# Register-ETW

[![Build & Release](https://github.com/getel-arch/C-Template/actions/workflows/build_and_release.yaml/badge.svg)](https://github.com/getel-arch/C-Template/actions/workflows/build_and_release.yaml)

A Windows ETW (Event Tracing for Windows) monitor that detects when the Windows Calculator (calc.exe) is launched.

## Features

- Uses ETW to monitor process creation events
- Detects when calc.exe is launched
- Real-time monitoring
- Minimal resource usage

## Usage

1. Run the program with administrative privileges
2. The program will start monitoring for calculator process creation
3. Launch the Windows Calculator to see the detection in action
4. Press Ctrl+C to stop monitoring

## Building

Compile using GCC:
```bash
gcc main.c -o etw_calc_monitor.exe
```

## Requirements

- Windows operating system
- Administrative privileges (required for ETW monitoring)
