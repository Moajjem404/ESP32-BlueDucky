$url = "https://images.unsplash.com/photo-1526374965328-7f61d4dc18c5?q=80&w=1920&auto=format&fit=crop" # Matrix Hacker Background
$path = "$env:TEMP\hacker_bg.jpg"

Write-Host "Downloading Wallpaper..." -ForegroundColor Yellow
Invoke-WebRequest -Uri $url -OutFile $path

$code = @"
using System.Runtime.InteropServices;
public class Wallpaper {
    [DllImport("user32.dll", CharSet = CharSet.Auto)]
    public static extern int SystemParametersInfo(int uAction, int uParam, string lpvParam, int fuWinIni);
}
"@

Add-Type -TypeDefinition $code
[Wallpaper]::SystemParametersInfo(0x0014, 0, $path, 0x01 -bor 0x02)

Write-Host "Wallpaper Changed Successfully!" -ForegroundColor Green
Start-Sleep -Seconds 2
