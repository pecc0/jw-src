set GROOVY_VERSION=1.7.3
set GROOVY_HOME=C:\programs\eclipse\plugins\org.codehaus.groovy_1.7.3.20100630-0900-e35
%~d0
cd %~dp0\..
java -cp "%GROOVY_HOME%\lib\groovy-all-%GROOVY_VERSION%.jar" groovy.lang.GroovyShell test\build.groovy %*
pause