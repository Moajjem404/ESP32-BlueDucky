Add-Type -AssemblyName System.Windows.Forms
for ($i=1; $i -le 3; $i++) {
    Start-Process notepad
    Start-Sleep -Seconds 1
    [System.Windows.Forms.SendKeys]::SendWait("System Compromised. Blue Ducky is everywhere...{ENTER}")
}
