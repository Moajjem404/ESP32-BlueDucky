[console]::OutputEncoding = [System.Text.Encoding]::UTF8
Clear-Host
Write-Host @"
__   ______  _   _   _   _  ___  _   _ _____   ____  _____ _____ _   _   _   _  ___  ____ _  __ _____ ____  
\ \ / / __ \| | | | | | | |/ _ \| | | | ____| | __ )| ____| ____| \ | | | | | |/ _ \/ ___| |/ /| ____|  _ \ 
 \ V / |  | | | | | | |_| | |_| | | | |  _|   |  _ \|  _| |  _| |  \| | | |_| | |_| | |  | ' / |  _| | | | |
  | || |__| | |_| | |  _  |  _  | |_| | |___  | |_) | |___| |___| |\  | |  _  |  _  | |__| . \ | |___| |_| |
  |_| \____/ \___/  |_| |_|_| |_|\___/|_____| |____/|_____|_____|_| \_| |_| |_|_| |_|\____|_|\_\|_____|____/ 
"@ -ForegroundColor Green

Write-Host ""
Write-Host "==========================================================" -ForegroundColor Red
Write-Host "           SYSTEM COMPROMISED BY ESP32 BLUEDUCKY          " -ForegroundColor White -BackgroundColor DarkRed
Write-Host "==========================================================" -ForegroundColor Red
Write-Host ""
Write-Host "Don't worry, this is just a friendly prank! :)" -ForegroundColor Yellow
Write-Host ""
Start-Sleep -Seconds 10
Exit
