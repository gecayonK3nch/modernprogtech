@echo off
chcp 65001 > log
del log

ctest -j 4 --output-on-failure --test-dir C:/Users/gecay/OneDrive/Desktop/Projects/modernprogtech/SemesterTwo/multiproject/build_ninja/sorting/test
