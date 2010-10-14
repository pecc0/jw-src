set GROOVY_HOME=C:\eclipse\plugins\org.codehaus.groovy_1.7.0.xx-20100115-0900-e35-RELEASE
%~d0
cd %~dp0\..
call scripts\build.bat test\build.groovy
pause