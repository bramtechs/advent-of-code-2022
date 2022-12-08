if ($args.Count -eq 1) {
    $day = $args[0]
}
else {
    $day = Read-Host "Enter number of day to run!"
}

New-Item -ItemType Directory -Force -Path .\build | Out-Null

if ($day -le 3) {
    $gofiles = Get-ChildItem -Filter *.go
    go run $gofiles $day
}
elseif ($day -ge 4 -and $day -le 6) {
    javac ".\day0$day.java" ".\utils.java" -d build
    java -classpath .\build "day0$day"
}
elseif ($day -ge 7 -and $day -le 8) {
    g++ "./day0$day.cpp" -o "./build/day0$day.exe"
    & ".\build\day0$day.exe"
}
else {
    Write-Error "Unknown day number"
}