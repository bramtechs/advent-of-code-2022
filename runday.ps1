$build_path = "build"

$day = "01"

if ($args[0]) {
    $day = $args[0]
}
else {
    $day = Read-Host "Enter day number?"
}

Write-Host $day

New-Item -ItemType Directory -Path $build_path -Force
cmake -S . -B $build_path
cmake --build $build_path

# make release builds
$exe_path = "$build_path\\Day$day\Debug\Day$day.exe"
Write-Host($exe_path)

Clear-Host
Write-Host "Output of day $day"
Write-Host "=============================="

& $exe_path