import java.io.File;

import groovy.lang.GroovyClassLoader;
import groovy.lang.Script;
import groovy.util.ConfigObject;
import groovy.util.ConfigSlurper;

class BuildMain extends Script {
	ConfigObject config;
	
	def buildIvy;
	def buildRevEng; 
	
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
	
	def addCP(String dir) {
		addCP(dir, ~/.*\.jar/);
	}
	
	def addCP(String dir, pattern) {
		addCP(this.class.classLoader, dir, pattern);
	}
	
	static def addCP(GroovyClassLoader gcl, String dir, pattern) {
		//println gcl.
		
		new File( dir ).eachFileMatch(pattern) {
			f -> 
			//println ">>$f";
			gcl.addClasspath(f.getAbsolutePath());
		}
	}
	
	def init() {
		if (config == null) {
        	def userHome = System.properties['user.home'];
        	
    		def scriptsRoot = args.length > 0 ? args[0] : 'scripts';
    		
    		ConfigSlurper cs = new ConfigSlurper();
    		
    		cs.binding = [scriptsRoot:scriptsRoot] + System.properties;
    		
        	config = cs.parse(new File("$scriptsRoot/build.conf").toURI().toURL());
    		
    		config.scriptsRoot = scriptsRoot;
    		
    		config.setConfigFile(new File("$scriptsRoot/build.conf").toURI().toURL());
    		
        	//Add the project specific conf
        	mergeConfig(config, 'build.conf');
        	
        	//Add the project specific conf
        	mergeConfig(config, 'local.build.conf');
    		
    		//Add PC specific conf
    		mergeConfig(config, "${config.ivy.dir}/local.build.conf");
		}
	}
	
	public static BuildMain inst(String[] args) {
		BuildMain script = new BuildMain();
		script.args = args;
		return script;
	}
	
	def ivy() {
		getBuildIvy().run(config, this);
	}
	
    def getBuildIvy() {
		if (buildIvy == null) {
			init()
			download(config.ivy.lib.url, config.ivy.jars.dir);
			download(config.ivy.svnresolver.url, config.ivy.jars.dir);
			download(config.ivy.svnkit.url, config.ivy.jars.dir);
			
			addCP(config.ivy.jars.dir)
			
			buildIvy = this.class.classLoader.parseClass(new File("${config.scriptsRoot}/BuildIvy.groovy")).newInstance()
		}
    	return buildIvy;
    }
	
	def reveng() {
		ivy();
		addCP(config.reveng.libs.dir);
		getBuildRevEng().run(config, this);
	}
	
	def getBuildRevEng() {
		if (buildRevEng == null) {
			buildRevEng = this.class.classLoader.parseClass(new File("${config.scriptsRoot}/BuildRevEng.groovy")).newInstance();
		}
    	return buildRevEng;
    }
	
	def clean() {
		
		getBuildIvy().clean();
	}
	
	def pack() {
		init();
		reveng()
	}
	
	def run() {
		pack()
		println 'complete'
	}
	
	public static void main(String[] args) {
		BuildMain script = inst(args);
		script.run();
	}
}
