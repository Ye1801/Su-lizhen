del *.scvd /s      
del *.lst /s   
del *.togetek /s
del *.ini /s
del *.mxproject /s

rd MDK-ARM\DebugConfig /s /Q
rd MDK-ARM\RTE /s /Q
rd MDK-ARM\stm32 /s /Q

del MDK-ARM\JLinkLog.txt  /s


exit
