import groovy.lang.GroovyClassLoader;
import groovy.lang.Script;

class BuildMain extends Script {
	ConfigObject config;
	
	def scriptsRoot
	
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
			config.merge(new ConfigSlurper().parse(f.toURI().toURL()))
		}
	}
	
	def init() {
	
    	def userHome = System.properties['user.home'];
    	
		scriptsRoot = args.length ? args[0] : 'scripts';
    	
    	config = new ConfigSlurper().parse(new File("$scriptsRoot/build.conf").toURI().toURL());
    	
    	config["scriptsRoot"] = scriptsRoot;
    	
    	File ivyJar = download("${config.jar.ivy}", "$userHome/.ivy2/jars");
    	
    	this.class.classLoader.addURL(ivyJar.toURI().toURL());
    	
    	
    	
    	//Add the project specific build.properties
    	mergeConfig(config, 'build.conf');
    	
    	//Add the project specific local.build.properties
    	mergeConfig(config, 'local.build.conf');
		
	}
	
	def ivy() {
		//cl.setDebug true;
		//println this.class.classLoader;
		def buildIvy = this.class.classLoader.parseClass(new File("$scriptsRoot/BuildIvy.groovy")).newInstance()
		
		buildIvy.run1(config);
	}
	
	def run() {
		init();
		ivy();
		println 'complete'
	}
	
	public static void main(String[] args) {
		BuildMain script = new BuildMain();
		script.args = args;
		script.run();
	}
}
