$current_preset="win-x64"
$lib_dir_for_copy="..\ASP.NET_MVC\Libraries"
$lib_name="ModelLibrary.dll"

cd ..\CalculatorLibraryCPP &&
cmake --preset=$current_preset &&
cmake --build --preset=$current_preset &&
mkdir -Force $lib_dir_for_copy &&
Copy-Item -Path ".\out\Debug\$lib_name" -Destination "$lib_dir_for_copy\$lib_name" &&
rm out -R &&
cd ..\ASP.NET_MVC &&
dotnet run
