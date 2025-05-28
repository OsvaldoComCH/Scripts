$Path = [System.Environment]::GetEnvironmentVariable("path", "User");
$PathItems = $Path.Split(";");
$SetCompiler = $true

foreach($p in $Path)
{
	if($p -match "D:\MSYS2\ucrt64\bin\")
	{
		$SetCompiler = $false;
	}
}

if($SetCompiler)
{
	$Path += ";D:\MSYS2\ucrt64\bin\";
}

[System.Environment]::SetEnvironmentVariable("path", $Path, "User");

$wallpaperPath = "$env:USERPROFILE\Pictures\wallpaper.jpg"

Copy-Item -Path ".\wallpaper.jpg" -Destination "$env:USERPROFILE\Pictures\" -Force

Set-ItemProperty -Path "HKCU:\Control Panel\Desktop" -Name Wallpaper -Value $wallpaperPath

# Aplica com a API do Windows
Add-Type @"
using System.Runtime.InteropServices;
public class Wallpaper {
    [DllImport("user32.dll", SetLastError = true)]
    public static extern bool SystemParametersInfo(int uAction, int uParam, string lpvParam, int fuWinIni);
}
"@
[Wallpaper]::SystemParametersInfo(20, 0, $wallpaperPath, 3)

cmdkey /generic:LegacyGeneric:target=git:https://github.com /user: /pass:

git config --global user.name ""
git config --global user.email ""

Set-Location -Path "$env:USERPROFILE\Documents\"

git clone https://github.com/nickyzz1/RecrutamentoInteligenteApi

Set-Location -Path "$env:USERPROFILE\Documents\RecrutamentoInteligenteApi\"

git fetch --prune origin
git checkout main
git pull

git clone https://github.com/nickyzz1/RecrutamentoInteligenteFront

Set-Location -Path "$env:USERPROFILE\Documents\RecrutamentoInteligenteFront\"

git fetch --prune origin
git checkout main
git pull