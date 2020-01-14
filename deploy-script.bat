@ECHO OFF

SETLOCAL

SET TEAM=BLUE
touch src\main.cpp
prosv5 make
prosv5 upload --slot 1 --name BLUE

SET TEAM=RED
touch src\main.cpp
prosv5 make
prosv5 upload --slot 2 --name RED

ENDLOCAL