set GROOVY_HOME=C:\eclipse\plugins\org.codehaus.groovy_1.7.0.xx-20100115-0900-e35-RELEASE
set SCRIPTS_DIR=%~dp0
java -cp "%GROOVY_HOME%\lib\groovy-all-1.7.0.jar" groovy.lang.GroovyShell "%SCRIPTS_DIR%\build.groovy" %SCRIPTS_DIR%
pause