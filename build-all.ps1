# Download Lua sources and build binary packages for Win32/Win64.

# Abort whenever a command fails.
$ErrorActionPreference = "Stop"

New-Item -Type Directory build-x64
Push-Location build-x64
cmake .. -A x64
cmake --build . --target create-zip --config RelWithDebInfo
Move-Item *.zip ..
Pop-Location

New-Item -Type Directory build-arm64
Push-Location build-arm64
cmake .. -A arm64
cmake --build . --target create-zip --config RelWithDebInfo
Move-Item *.zip ..
Pop-Location

New-Item -Type Directory build-x86
Push-Location build-x86
cmake .. -A Win32
cmake --build . --target create-zip --config RelWithDebInfo
Move-Item *.zip ..
Pop-Location
