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
			result.withWriter {
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
		
		//Load all needed classes here ...
		File ivyJar = download(config.ivy.lib, config.ivy.jars.dir);
		this.class.classLoader.addURL(ivyJar.toURI().toURL());
	}
	
	public static BuildMain inst(String[] args) {
		BuildMain script = new BuildMain();
		script.args = args;
		script.init();
		return script;
	}
	
	def ivy() {
		//cl.setDebug true;
		//println this.class.classLoader;
		def buildIvy = this.class.classLoader.parseClass(new File("${config.scriptsRoot}/BuildIvy.groovy")).newInstance()
		
		buildIvy.run(config);
	}
	
	def clean() {
		
	}
	
	def run() {
		ivy();
		println 'complete'
	}
	
	public static void main(String[] args) {
		BuildMain script = inst(args);
		script.run();
	}
}
