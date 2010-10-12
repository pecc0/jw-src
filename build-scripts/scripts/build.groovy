
def download(address, dst)
{
	File dstDir = new File(dst);
	if (!dstDir.exists()) {
		dstDir.mkdirs();
	}
	File result = new File(dstDir, address.tokenize("/")[-1]);
	
	if (result.exists()) {
		
	} else {
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

def userHome = System.properties['user.home'];

def scriptsRoot = args.length ? args[0] : 'scripts';

ConfigObject config = new ConfigSlurper().parse(new File("$scriptsRoot/build.properties").toURI().toURL());

config["scriptsRoot"] = scriptsRoot;

File ivyJar = download('http://repo1.maven.org/maven2/org/apache/ivy/ivy/2.2.0/ivy-2.2.0.jar', "$userHome/.ivy2/jars");

this.class.classLoader.addURL(ivyJar.toURI().toURL());

def buildIvy = this.class.classLoader.parseClass(new File("$scriptsRoot/BuildIvy.groovy")).newInstance()

//Add the project specific build.properties
mergeConfig(config, 'build.properties');

//Add the project specific local.build.properties
mergeConfig(config, 'local.build.properties');

buildIvy.run(config);

println 'complete'