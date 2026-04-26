Add-Type -AssemblyName System.Speech
$synth = New-Object System.Speech.Synthesis.SpeechSynthesizer
$synth.Volume = 100
$synth.Rate = 0
$synth.Speak("Attention! Attention! This computer is now under the control of E S P 32 Blue Ducky. Your system has been compromised. Just kidding, have a nice day!")
