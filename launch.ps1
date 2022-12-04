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
elseif ($day -eq 4) {
    New-Item -ItemType Directory -Force -Path .\build | Out-Null
    javac ".\day0$day.java" -d build
    Set-Location build
    java "day0$day"
    Set-Location ..
}
else {
    Write-Error "Unknown day number"
}