$current_preset="win-x64"
$lib_dir_for_copy="..\MAUI\MyCalculator_v3.0\Libraries"
$lib_name="ModelLibrary.dll"
$target_framework = "net8.0-windows10.0.19041.0"
$configuration = "win10-x64"
$open_path = ".\MyCalculator_v3.0\bin\Debug\$target_framework\$configuration\publish\MyCalculator.exe"

cd ..\CalculatorLibraryCPP &&
cmake --preset=$current_preset &&
cmake --build --preset=$current_preset &&
mkdir $lib_dir_for_copy &&
Copy-Item -Path ".\out\Debug\$lib_name" -Destination "$lib_dir_for_copy\$lib_name" &&
rm out -R &&
cd ..\MAUI &&
dotnet publish .\MyCalculator_v3.0 -f $target_framework -c Debug -p:RuntimeIdentifierOverride=$configuration -p:WindowsPackageType=None &&
explorer.exe $open_path