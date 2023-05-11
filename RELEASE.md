1. Create a release build using Visual Studio 64-bit
2. Copy release folder (should be in build/release) to another location (example: "C:\Users\xxx\Desktop\Release"
3. Remove everything except melonpan.exe, .dll file and .res file
5. Navigate to Qt 5.15.1 compiler binary folder (e,g, C:\Qt\5.15.1\msvc2019_64\bin)
6. Open Powershell in that folder and run winqtdeploy.exe with argument pointing to location of release folder in 2
   - example: .\windeployqt.exe "C:\Users\xxx\Desktop\Release"
7. Copy resource folder (res) from source code to the Release folder
8. Done!