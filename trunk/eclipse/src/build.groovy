//groovy.grape.Grape.initGrape()
import groovy.grape.Grape;
import groovy.grape.GrapeIvy;

def jwgrape = new GroovyClassLoader().parseClass(new File('src/groovy/grape/JWGrape.groovy')).newInstance();

jwgrape.grab([group:'org.hibernate', module:'hibernate-tools', version:'3.2.3.GA', conf:'ear->default'])

jwgrape.grab([group:'org.hibernate', module:'jtidy', version:'r8-21122004', conf:'ear->default'])

jwgrape.copyAll();

//Grape.grab([group:'org.hibernate', module:'hibernate-tools', version:'3.2.3.GA']);

//println Grape.resolve([group:'org.hibernate', module:'hibernate-tools', version:'3.2.3.GA', autoDownload:true, calleeDepth:4])

//println Grape.resolve([group:'org.hibernate', module:'hibernate-tools', version:'3.2.3.GA', blabla:'dsds', autoDownload:true, calleeDepth:4]);

println Grape.enumerateGrapes();
println 'complete'



