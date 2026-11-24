# Chay recipe bang cmd.exe de lenh del hoat dong ca trong cmd, PowerShell va Git Bash.
SHELL := cmd.exe
.SHELLFLAGS := /C

CXX      ?= g++
CXXFLAGS ?= -std=c++14 -Wall -Wextra -pedantic -O2 -Iinclude
LDFLAGS  ?= -static

CORE := src/Course.cpp src/Student.cpp

.PHONY: all demo run clean

all: demo

demo: $(CORE) src/main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@.exe $(LDFLAGS)

run: demo
	demo.exe

clean:
	-del /q demo.exe 2>nul
