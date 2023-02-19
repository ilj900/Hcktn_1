cd C:\Work_Projects\Template_C++_Project
Remove-Item -path .\build\CMakeCache.txt
cmake -G "Visual Studio 16 2019" -B build -A x64
