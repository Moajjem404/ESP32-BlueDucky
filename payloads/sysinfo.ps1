Clear-Host
$b = [char]27 + "[1m"
$r = [char]27 + "[0m"

Write-Host ""
Write-Host "$b================================================================$r" -ForegroundColor DarkGray
Write-Host "$b                   SYSTEM INFORMATION GRABBER                   $r" -ForegroundColor White -BackgroundColor DarkBlue
Write-Host "$b================================================================$r" -ForegroundColor DarkGray
Write-Host ""

Write-Host "$b[*] Gathering System Data... Please wait.$r" -ForegroundColor Yellow
Write-Host ""

# Gather System Data
try { $os = Get-CimInstance Win32_OperatingSystem; $osName = $os.Caption } catch { $osName = "Unknown" }
try { $cpu = Get-CimInstance Win32_Processor; $cpuName = $cpu.Name } catch { $cpuName = "Unknown" }
try { $ram = [math]::Round($os.TotalVisibleMemorySize / 1MB, 2); $ramString = "$ram GB" } catch { $ramString = "Unknown" }

# Gather Network Data
try {
    $localIp = (Get-NetIPAddress -AddressFamily IPv4 -InterfaceAlias Wi-Fi, Ethernet -ErrorAction SilentlyContinue | Select-Object -First 1).IPAddress
    if ([string]::IsNullOrEmpty($localIp)) {
        $localIp = (Get-NetIPAddress -AddressFamily IPv4 -InterfaceAlias * -ErrorAction SilentlyContinue | Where-Object IPAddress -ne "127.0.0.1" | Select-Object -First 1).IPAddress
    }
} catch { $localIp = "Unknown" }

try { $mac = (Get-NetAdapter -ErrorAction SilentlyContinue | Where-Object Status -eq "Up" | Select-Object -First 1).MacAddress } catch { $mac = "Unknown" }

try { $publicIp = (Invoke-RestMethod -Uri 'https://api.ipify.org' -TimeoutSec 3 -ErrorAction Stop) } catch { $publicIp = "Unable to fetch" }

# User Info
$user = $env:USERNAME
$computer = $env:COMPUTERNAME

# Display Data
Write-Host "$b[+] SYSTEM DETAILS $r" -ForegroundColor Cyan
Write-Host "----------------------------------" -ForegroundColor DarkGray
Write-Host "$b Computer Name :$r $computer"
Write-Host "$b Current User  :$r $user"
Write-Host "$b OS Version    :$r $osName"
Write-Host ""

Write-Host "$b[+] HARDWARE INFO $r" -ForegroundColor Cyan
Write-Host "----------------------------------" -ForegroundColor DarkGray
Write-Host "$b Processor     :$r $cpuName"
Write-Host "$b Total RAM     :$r $ramString"
Write-Host ""

Write-Host "$b[+] NETWORK INFO $r" -ForegroundColor Cyan
Write-Host "----------------------------------" -ForegroundColor DarkGray
Write-Host "$b Local IP      :$r $localIp"
Write-Host "$b Public IP     :$r $publicIp"
Write-Host "$b MAC Address   :$r $mac"
Write-Host ""

Write-Host "$b================================================================$r" -ForegroundColor DarkGray
Write-Host "$b[!] Data extraction complete.$r" -ForegroundColor Green
Write-Host ""

Start-Sleep -Seconds 15
Exit
