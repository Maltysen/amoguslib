g++ --std=gnu++14 -I%~dp0 -g -O3 -Wall -Wshadow -Wno-sign-compare %1.cpp -o %1 2>&1 | more

if not exist "out" mkdir "out"
if exist out\%1out.cpp del out\%1out.cpp
echo "#include <bits/stdc++.h>" >> out\%1out.cpp

cpp -I%~dp0 %1.cpp -DCOPIER  >> out\%1out.cpp
