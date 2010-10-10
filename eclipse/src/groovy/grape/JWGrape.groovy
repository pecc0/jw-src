package groovy.grape

import java.io.File;
import java.util.Map;

class JWGrape extends Grape {
	private Map props = [:];
	
	public JWGrape() {
	}
	
	public void setProp(String key, String val) {
		props[key] = val;
	}
	
	public def dl(Map<String, Object> dependency) {
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
		URI[] cache = super.resolve(dependency);
		
		String libRoot = props.libRoot ?: 'lib';
		
		cache.each {
			File src = new File(it);
			File dst = new File(libRoot, dstConf);
			def reader = src.newReader()
			dst.withWriter { writer -> writer << reader }
			reader.close();
		}
		
		
	}
}
