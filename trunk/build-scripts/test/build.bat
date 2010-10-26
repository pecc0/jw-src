set GROOVY_VERSION=1.7.0
set GROOVY_HOME=C:\eclipse\plugins\org.codehaus.groovy_1.7.0.xx-20100115-0900-e35-RELEASE
%~d0
cd %~dp0\..
java -cp "%GROOVY_HOME%\lib\groovy-all-%GROOVY_VERSION%.jar" groovy.lang.GroovyShell test\build.groovy %*
pause