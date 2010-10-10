//groovy.grape.Grape.initGrape()
import groovy.grape.Grape;
import groovy.grape.GrapeIvy;

//GroovyClassLoader groovyClassLoader = new GroovyClassLoader();

//def jwgrape = groovyClassLoader.parseClass(new File('src/groovy/grape/JWGrape.groovy')).newInstance();

//jwgrape.dl([group:'org.hibernate', module:'hibernate-tools', version:'3.2.3.GA', conf:'ear->default'])

//println Grape.resolve([group:'org.hibernate', module:'hibernate-tools', version:'3.2.3.GA', autoDownload:true, calleeDepth:4])

println Grape.resolve([group:'org.hibernate', module:'hibernate-tools', version:'3.2.3.GA', blabla:'dsds', autoDownload:true, calleeDepth:4]);
println 'complete'

//println Grape.enumerateGrapes();

