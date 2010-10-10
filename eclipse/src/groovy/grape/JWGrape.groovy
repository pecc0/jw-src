package groovy.grape

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Map;

class JWGrape extends Grape {
	private Map props = [:];
	
	private static List dependencies = [];
	
	public JWGrape() {
	}
	
	public void setProp(String key, String val) {
		props[key] = val;
	}
	
	public static void grab(Map<String, Object> dependency) {
		dependency.autoDownload = true;
		dependency.calleeDepth = dependency.calleeDepth?:GrapeIvy.DEFAULT_DEPTH + 1;
		String srcConf = dependency.conf ?: 'default';
		String dstConf;
		String[] parts = srcConf.split('->');
		if (parts.length > 1) {
			srcConf = parts[1];
			dstConf = parts[0];
		} else {
			dstConf = srcConf;
		}
		dependency.conf = srcConf;
		dependency.dstConf = dstConf;
		Grape.grab(dependency);
		dependencies.add dependency
	}
	
	public def copyAll() {
		
		dependencies.each {
			dependency ->
			URI[] cache = Grape.resolve(dependency);
			
			String libRoot = props.libRoot ?: 'lib';
			
			File dstDir = new File(libRoot, dependency.dstConf);
			
			if (!dstDir.exists()) {
				dstDir.mkdirs();
			}
			if (!dstDir.isDirectory()) {
				throw new FileNotFoundException("$dstDir must be directory");
			}
			
			cache.each {
				File src = new File(it);
				File dst = new File(dstDir, src.getName());
				println ">>$dst"
				def reader = src.newReader()
				//dst.withWriter { writer -> writer << reader }
				reader.close();
			}
		}
		
		
		
	}
}
