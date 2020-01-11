@ECHO OFF

SETLOCAL

SET TEAM=BLUE
prosv5 make all
prosv5 upload --slot 1 --name BLUE

SET TEAM=RED
prosv5 make all
prosv5 upload --slot 2 --name RED

ENDLOCAL