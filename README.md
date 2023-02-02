# Inlämningsuppgift 1 del 2.

Instruktioner finns i Omniway.



Nedan är lite support för att kunna köra google test i C++. Det finns nu två strukturer. En där man inte behöver köra CMake (men får istället problem med att kunna bygga både en vanlig fil och test executable). Samt en som använder byggmiljön CMake.

## C++ bygge med CMake
Mappen Cpp innehåller filerna för C++ strukturen. 

Detta är ungefär hur man skulle sätta upp det i ett riktigt projekt:

 - main.cpp: Huvudfilen
 - deck.cpp: Vår modul
 - include/deck.h: Headerfil för vår modul
 - tests/test_deck.cpp: Testfil för vår modul
 - CMakeLists.txt: Filen som beskriver bygget, inklusive test executable.

#### Installation

Öppna MSYS MINGW64. Installera följande:

```
pacman -S mingw-w64-x86_64-cmake
pacman -S ninja
```

Det finns Cmake extension för VS Code. Jag har fått problem att köra direkt från VS code så jag rekommenderar inte att installera det.

Vissa anpassningar av CMake filen kan behövas om du inte använder Windows eller MinGW64.

#### Bygge

Öppna MSYS MINGW64. Gå till mappen där du har ditt program (där main.cpp ligger).

Vi behöver köra CMake en gång för att skapa byggfilerna.

```
# Assuming you're executing these commands
# from the root directory!
mkdir build && cd build
cmake ..
```

Har inget i strukturen ändrats kan vi sedan köra följande kommando varje gång vi vill bygga:

```
cmake --build .
```

Våra executables har nu skapats. Vill du sedan köra själva programmet (main-funktionen) kör du:
```
./deck.exe
```

För att köra testerna kör du:
```
./test-deck.exe
```
