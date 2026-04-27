Clear-Host
$b = [char]27 + "[1m"
$r = [char]27 + "[0m"
Write-Host ""
Write-Host "$b __   _____  _   _   _   _    _    _   _ _____ $r" -ForegroundColor Red
Write-Host "$b \ \ / / _ \| | | | | | | |  / \  | | | | ____|$r" -ForegroundColor Red
Write-Host "$b  \ V / (_) | |_| | | |_| | / _ \ | | | |  _|  $r" -ForegroundColor Red
Write-Host "$b   | | \___/ \___/  |  _  |/ ___ \| |_| | |___ $r" -ForegroundColor DarkRed
Write-Host "$b   |_|              |_| |_/_/   \_\\___/|_____|$r" -ForegroundColor DarkRed
Write-Host ""
Write-Host "$b  ____  _____ _____ _   _   _   _    _    ____ _  _______ ____  $r" -ForegroundColor Red
Write-Host "$b | __ )| ____| ____| \ | | | | | |  / \  / ___| |/ / ____|  _ \ $r" -ForegroundColor Red
Write-Host "$b |  _ \|  _| |  _| |  \| | | |_| | / _ \| |   | ' /|  _| | | | |$r" -ForegroundColor Red
Write-Host "$b | |_) | |___| |___| |\  | |  _  |/ ___ \ |___| . \| |___| |_| |$r" -ForegroundColor DarkRed
Write-Host "$b |____/|_____|_____|_| \_| |_| |_/_/   \_\____|_|\_\_____|____/ $r" -ForegroundColor DarkRed
Write-Host ""
Write-Host "$b================================================================$r" -ForegroundColor DarkGray
Write-Host "$b             SYSTEM COMPROMISED BY ESP32 BLUEDUCKY              $r" -ForegroundColor White -BackgroundColor DarkRed
Write-Host "$b================================================================$r" -ForegroundColor DarkGray
Write-Host ""
Write-Host "$b [!] Unauthorized access detected.$r" -ForegroundColor Yellow
Write-Host "$b [!] Data exfiltration initiated...$r" -ForegroundColor Yellow
Write-Host ""
Write-Host "$b Don't worry, this is just a friendly prank! :)$r" -ForegroundColor Green
Write-Host ""
Start-Sleep -Seconds 10
Exit
