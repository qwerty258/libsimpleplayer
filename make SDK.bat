cd ".\MSVS\VS2013\x64\Release"
copy "libSimplePlayer.dll"  "..\..\..\..\libSimplePlayerSDK\bin\64bit"
copy "libvlc.dll"           "..\..\..\..\libSimplePlayerSDK\bin\64bit"
copy "libvlccore.dll"       "..\..\..\..\libSimplePlayerSDK\bin\64bit"
copy "testPlayer.exe"       "..\..\..\..\libSimplePlayerSDK\bin\64bit"
xcopy "plugins"             "..\..\..\..\libSimplePlayerSDK\bin\64bit\plugins" /E

copy "libSimplePlayer.lib"  "..\..\..\..\libSimplePlayerSDK\lib\64bit"

cd "..\..\x86\Release"
copy "libSimplePlayer.dll"  "..\..\..\..\libSimplePlayerSDK\bin\32bit"
copy "libvlc.dll"           "..\..\..\..\libSimplePlayerSDK\bin\32bit"
copy "libvlccore.dll"       "..\..\..\..\libSimplePlayerSDK\bin\32bit"
copy "testPlayer.exe"       "..\..\..\..\libSimplePlayerSDK\bin\32bit"
xcopy "plugins"             "..\..\..\..\libSimplePlayerSDK\bin\32bit\plugins" /E

copy "libSimplePlayer.lib"  "..\..\..\..\libSimplePlayerSDK\lib\32bit"

cd "..\..\..\..\include"
copy *.h                    "..\libSimplePlayerSDK\include"