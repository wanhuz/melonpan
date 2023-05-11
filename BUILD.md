1. Install MS Visual Studio 2022
2. Install Qt 5.15.1 
3. Integrate Qt into Visual Studio using QT VS Tools Plugin
   - Set Qt 5.15.1 to its folder (example: C:\Qt\5.15.1\msvc2019_64)
4. Install Vcpkg  
5. Install Mecab from official site, set to UTF-8 during installation
6. Build the project from Visual Studio to download dependencies using Vcpkg and run it!

x. If the program crash because of Mecab::createTagger, make sure the mecabrc path is correct in mecabKey.cpp