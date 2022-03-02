@echo off
g++ --std=gnu++14 -I%~dp0\.. -g -O3 -Wall -Wshadow -Wno-sign-compare %1.cpp -o %1 2>&1 | more

if not exist "out" mkdir "out"
if exist out\%1_out.cpp del out\%1_out.cpp
echo|set /p="#include <bits/stdc++.h>" > out\%1_out.cpp
echo. >> out\%1_out.cpp

cpp -I%~dp0\.. %1.cpp -DCOPIER  >> out\%1_out.cpp
