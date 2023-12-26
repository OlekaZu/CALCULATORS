#!/bin/bash

$current_preset="default"
$lib_dir_for_copy="../ASP.NET_MVC/Libraries"
$lib_name="ModelLibrary.dll"

cd ../CalculatorLibraryCPP
cmake --preset=$current_preset
cmake --build --preset=$current_preset 
mkdir -p $lib_dir_for_copy 
cp out/$lib_name $lib_dir_for_copy/$lib_name
rm -rf out
cd ../ASP.NET_MVC
dotnet run
