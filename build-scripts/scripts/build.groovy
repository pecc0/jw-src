
def download(address, dst)
{
	File dstDir = new File(dst);
	if (!dstDir.exists()) {
		dstDir.mkdirs();
	}
	new File(dstDir, address.tokenize("/")[-1]).withWriter {
		out ->
		out << new URL(address).openStream()
	}
}

def userHome = System.properties['user.home'];
download('http://repo1.maven.org/maven2/org/apache/ivy/ivy/2.2.0/ivy-2.2.0.jar', "$userHome/.ivy2/jars");

this.class.classLoader.rootLoader.addURL(new File("$userHome/.ivy2/jars/ivy-2.2.0.jar").toURI().toURL());

this.class.classLoader.parseClass(new File('scripts/groovy_ivy.groovy')).newInstance()

println 'complete'