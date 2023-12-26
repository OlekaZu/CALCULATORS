#!/bin/bash

$current_preset="default"
$lib_dir_for_copy="../MAUI/MyCalculator_v3.0/Libraries"
$lib_name="ModelLibrary.dll"
$target_framework = "net8.0-maccatalyst"
$configuration = "maccatalyst-x64"
$open_path = "./MyCalculator_v3.0/bin/Debug/$target_framework/$configuration/publish/MyCalculator"

cd ../CalculatorLibraryCPP
cmake --preset=$current_preset
cmake --build --preset=$current_preset
mkdir -p $lib_dir_for_copy
cp out/$lib_name $lib_dir_for_copy/$lib_name
rm -rf out
cd ../MAUI
dotnet publish ./MyCalculator_v3.0 -f $target_framework -c Debug -p:RuntimeIdentifier=$configuration
open $open_path
