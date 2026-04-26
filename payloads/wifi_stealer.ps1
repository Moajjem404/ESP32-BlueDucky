$output = "$env:USERPROFILE\Desktop\WiFi_Passwords.txt"
"==============================" | Out-File $output
"    SAVED WIFI PASSWORDS      " | Out-File -Append $output
"==============================" | Out-File -Append $output

$profiles = (netsh wlan show profiles) | Select-String "\:(.+)$" | ForEach-Object { $_.Matches.Groups[1].Value.Trim() }

foreach ($profile in $profiles) {
    $key = (netsh wlan show profile name="$profile" key=clear) | Select-String "Key Content\W+\:(.+)$" | ForEach-Object { $_.Matches.Groups[1].Value.Trim() }
    if ($key) {
        "SSID: $profile `nPassword: $key`n" | Out-File -Append $output
    } else {
        "SSID: $profile `nPassword: [NO PASSWORD]`n" | Out-File -Append $output
    }
}

Write-Host "All WiFi passwords have been successfully saved to Desktop\WiFi_Passwords.txt" -ForegroundColor Green
Start-Sleep -Seconds 3
