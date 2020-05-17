@ECHO OFF
REM # --------------------- #
REM # (C) 2020 madoodia.com #
REM # --------------------- #


SETLOCAL

REM set file=C:\Users\l72rugschiri\Desktop\fs.cfg
REM FOR %%i IN ("%file%") DO (
REM ECHO filedrive=%%~di
REM ECHO filepath=%%~pi
REM ECHO filename=%%~ni
REM ECHO fileextension=%%~xi
REM )

REM # -----= Getting Inputs =---- #
call "%VCVARS_LOCATION%/vcvarsall.bat" x64

set ROOT=%1
set FOLDER=%2
set FILE_NAME=%3

for %%i IN ("%ROOT%") do (
set FILE_PATH=%%~pi
set BASE_NAME=%%~ni
)

set TARGET_NAME=%FOLDER%

REM # ------= Include Envs =----- #
set LINUX_DIR=%~dp0
call %LINUX_DIR%envVars.bat
REM # --------------------------- #

echo "ROOT:" %ROOT%
echo "OUTPUT_FILE_EXTENSION:" %OUTPUT_FILE_EXTENSION%
echo "FOLDER:" %FOLDER%
echo "ROOT/FOLDER:" %ROOT%/%FOLDER%
echo "FILE_NAME:" %FILE_NAME%
echo "BASE_NAME:" %BASE_NAME%
echo "TARGET_NAME:" %TARGET_NAME%
echo "LINUX_DIR:" %LINUX_DIR%
echo "SDKS_LOCATION:" %SDKS_LOCATION%
echo "NEED_BUILD:" %NEED_BUILD%

REM ---------------------------

REM # --------- Common ---------- #
cd %ROOT%

if exist %TARGET_NAME%.%OUTPUT_FILE_EXTENSION% ( 
    del "%TARGET_NAME%.%OUTPUT_FILE_EXTENSION%"
)

if exist build (
    if %NEED_BUILD% equ 1 (
        rmdir /s /q build
    )
) 

if not exist build ( 
    mkdir build
)

if exist build ( 
    cd build
)


cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=%EXTRA_PREFIX_PATH% %ROOT%/%FOLDER%
cmake --build .

REM # ---= Workspace Project =--- #
REM # --------- Release --------- #
if "%FOLDER%" equ "." ( copy src/%TARGET_NAME%.%OUTPUT_FILE_EXTENSION% %ROOT%)
REM # --------------------------- #

REM # ----= Folder Project =----- #
REM # -----= File Project =------ #
REM # --------- Release --------- #
if not "%FOLDER%" equ "." ( copy %TARGET_NAME%.%OUTPUT_FILE_EXTENSION% %ROOT%)
REM # --------------------------- #

REM # ---= Running EXE File =---- #
cd %ROOT%
if %OUTPUT_FILE_EXTENSION% equ "exe" (
    if exist %TARGET_NAME%.%OUTPUT_FILE_EXTENSION% (
        %TARGET_NAME%.%OUTPUT_FILE_EXTENSION%
        REM %TARGET_NAME%.%OUTPUT_FILE_EXTENSION% --gtest_output="xml:./$TARGET_NAME.xml"
    )
)
REM # --------------------------- #