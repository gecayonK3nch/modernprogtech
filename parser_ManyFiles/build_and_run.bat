@echo off
set BUILD_DIR=build

if exist %BUILD_DIR% (
    echo Удаление папки сборки...
    rmdir /s /q %BUILD_DIR%
)

mkdir %BUILD_DIR%
cd %BUILD_DIR%

echo Генерация сборочных файлов...
cmake .. || goto :error

echo Компиляция проекта...
cmake --build . || goto :error

cd Debug

echo Запуск программы...
parser.exe
if %ERRORLEVEL% neq 0 (
    echo Ошибка при выполнении программы, код ошибки: %ERRORLEVEL%
    pause
    exit /b 1
)

goto :end

:end
cd ..
cd ..
echo Сборка и выполнение завершены успешно.
pause

