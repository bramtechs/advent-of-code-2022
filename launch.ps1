if ($args.Count -eq 1) {
    $day = $args[0]
}
else {
    $day = Read-Host "Enter number of day to run!"
}

if ($day -le 3) {
    $gofiles = Get-ChildItem -Filter *.go
    go run $gofiles $day
}
elseif ($day -ge 4 -and $day -le 5) {
    New-Item -ItemType Directory -Force -Path .\build | Out-Null
    javac ".\day0$day.java" ".\utils.java" -d build
    java -classpath .\build "day0$day"
}
else {
    Write-Error "Unknown day number"
}