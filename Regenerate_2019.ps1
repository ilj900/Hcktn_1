cd C:\Work_Projects\Hcktn_1
Remove-Item -path .\build\CMakeCache.txt
cmake -G "Visual Studio 16 2019" -B build -A x64
