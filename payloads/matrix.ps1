$Host.UI.RawUI.WindowTitle = "System Hacked"
$Host.UI.RawUI.BackgroundColor = "Black"
$Host.UI.RawUI.ForegroundColor = "Green"
Clear-Host

$chars = [char[]]([char]33..[char]126)
$random = New-Object System.Random

while ($true) {
    $line = ""
    for ($i = 0; $i -lt 120; $i++) {
        if ($random.Next(0, 10) -gt 7) {
            $line += $chars[$random.Next(0, $chars.Length)]
        } else {
            $line += " "
        }
    }
    Write-Host $line -NoNewline
    Start-Sleep -Milliseconds 15
}
