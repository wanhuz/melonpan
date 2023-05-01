1. Install MS Studio 2022
2. Install Qt 5.15.1
3. Install Vcpkg  
4. Build the project from Visual Studio once to download dependencies using Vcpkg
5. Install Mecab from official site, set to UTF-8 during installation
6. To compile and run the program in debug mode, define absolute path to its resource folder in directive in file:
- dict.cpp
- MainWindow.cpp
- mecabKey.cpp
- ocr.cpp
- popup.cpp

x. If the program crash because of Mecab::createTagger, make sure the mecabrc absolute path is correct in mecabKey.cpp