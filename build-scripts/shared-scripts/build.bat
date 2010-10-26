set SCRIPTS_DIR=%~dp0
java -cp "%GROOVY_HOME%\lib\groovy-all-1.7.0.jar" groovy.lang.GroovyShell %1 %SCRIPTS_DIR%
