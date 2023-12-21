$current_platform = "x64"
$target_framework = "net8.0-windows10.0.19041.0"
$configuration = "win10-x64"
$open_path = ".\MyCalculator_v3.0\bin\Debug\$target_framework\$configuration\publish\MyCalculator.exe"

msbuild .\ModelLibrary /p:Configuration=Release /p:Platform=$current_platform && 
dotnet publish .\MyCalculator_v3.0 -f $target_framework -c Debug -p:RuntimeIdentifierOverride=$configuration -p:WindowsPackageType=None &&
explorer.exe $open_path

