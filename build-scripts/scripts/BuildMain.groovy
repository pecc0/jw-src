import java.io.File;

import groovy.lang.GroovyClassLoader;
import groovy.lang.Script;
import groovy.util.ConfigObject;
import groovy.util.ConfigSlurper;

class BuildMain extends Script {
	ConfigObject config;
	
	def download(address, dst)
	{
		File dstDir = new File(dst);
		if (!dstDir.exists()) {
			dstDir.mkdirs();
		}
		File result = new File(dstDir, address.tokenize("/")[-1]);
		
		if (result.exists()) {
			
		} else {
			println "downloading from $address...";
			result.withOutputStream {
				out ->
				out << new URL(address).openStream()
			}
		}
		return result;
	}
	
	def mergeConfig(ConfigObject config, path) {
		File f = new File(path);
		if (f.exists()) {
			ConfigSlurper cs = new ConfigSlurper();
			cs.binding = config.flatten() + System.properties;
			config.merge(cs.parse(f.toURI().toURL()))
		}
	}
	
	def addCP(String dir, pattern) {
		new File( dir ).eachFileMatch(pattern) {
			f -> 
			this.class.classLoader.addClasspath(f.getAbsolutePath());
		}
	}
	
	def init() {
    	def userHome = System.properties['user.home'];
    	
		def scriptsRoot = args.length > 0 ? args[0] : 'scripts';
		
		ConfigSlurper cs = new ConfigSlurper();
		
		cs.binding = [scriptsRoot:scriptsRoot] + System.properties;
		
    	config = cs.parse(new File("$scriptsRoot/build.conf").toURI().toURL());
		
		config.scriptsRoot = scriptsRoot;
		
		config.setConfigFile(new File("$scriptsRoot/build.conf").toURI().toURL());
		
    	//Add the project specific build.properties
    	mergeConfig(config, 'build.conf');
    	
    	//Add the project specific local.build.properties
    	mergeConfig(config, 'local.build.conf');
	}
	
	public static BuildMain inst(String[] args) {
		BuildMain script = new BuildMain();
		script.args = args;
		script.init();
		return script;
	}
	
	def ivy() {
		File ivyJar = download(config.ivy.lib, config.ivy.jars.dir);
		this.class.classLoader.addClasspath(ivyJar.getAbsolutePath());
		this.class.classLoader.addClasspath(config.ivy.jars.dir + '/ivysvnresolver.jar')
		this.class.classLoader.addClasspath(config.ivy.jars.dir + '/svnkit.jar');
		
		//println this.class.classLoader;
		def buildIvy = this.class.classLoader.parseClass(new File("${config.scriptsRoot}/BuildIvy.groovy")).newInstance()
		
		buildIvy.run(config);
	}
	
	def reveng() {
		ivy();
		
		//this.class.classLoader.addClasspath(config.reveng.hibernate.tools.jar);
		addCP('lib/generate-entities/', ~/.*\.jar/)

		def buildRevEng = this.class.classLoader.parseClass(new File("${config.scriptsRoot}/BuildRevEng.groovy")).newInstance()
		buildRevEng.run(config);
	}
	
	def clean() {
		
	}
	
	def run() {
		init();
		reveng()
		println 'complete'
	}
	
	public static void main(String[] args) {
		BuildMain script = inst(args);
		script.run();
	}
}
