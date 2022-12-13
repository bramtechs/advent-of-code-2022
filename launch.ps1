if ($args.Count -eq 1) {
    $day = $args[0]
}
else {
    $day = Read-Host "Enter number of day to run!"
}

Write-Host "Running day $day"

New-Item -ItemType Directory -Force -Path .\build | Out-Null

if ($day -le 3) {
    $gofiles = Get-ChildItem -Filter *.go
    Measure-Command { go run $gofiles $day | Out-Default }
    Write-Host "Timing for go includes build time"
}
elseif ($day -ge 4 -and $day -le 6) {
    javac ".\day0$day.java" ".\utils.java" -d build
    Measure-Command { java -classpath .\build "day0$day" | Out-Default }
}
elseif ($day -ge 7 -and $day -le 9) {
    cl "./day0$day.cpp" -o "./build/day0$day.exe"
    Measure-Command { & ".\build\day0$day.exe" | Out-Default }
}
elseif ($day -ge 10 -and $day -le 12) {
    Measure-Command { & php day$day.php | Out-Default }
}
elseif ($day -ge 13 -and $day -le 16) {
    Remove-Item -Force ".\build\cpp\Day$day.exe" | Out-Null
    haxe .\build.hxml
    Measure-Command { & ".\build\cpp\Day$day.exe" | Out-Default }
}
else {
    Write-Error "Unknown day number"
}
