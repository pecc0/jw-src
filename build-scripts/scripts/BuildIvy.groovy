import groovy.lang.GroovyClassLoader;
import groovy.util.ConfigObject;

import org.apache.ivy.Ivy;
import org.apache.ivy.core.module.descriptor.ModuleDescriptor;
import org.apache.ivy.core.report.ResolveReport;
import org.apache.ivy.core.retrieve.RetrieveOptions;
import org.apache.ivy.core.settings.IvySettings;
import org.apache.ivy.plugins.resolver.DependencyResolver;


class BuildIvy {
    	
    public void run(ConfigObject config, main) {
		GroovyClassLoader gcl = this.class.classLoader.parent;
		//println '>>>' + fm.last.ivy.plugins.svnresolver.SvnResolver.class.classLoader
		//println '>>>' + DependencyResolver.class.classLoader
		
        Ivy ivy = Ivy.newInstance();
		
		if (!config.containsKey('svnUserName') || !config.containsKey('svnUserPassword')) {
			println "Please, add your svnUserName and svnUserPassword in local.build.conf: \n" +
					"  svnUserName='username'\n" +
					"  svnUserPassword='password'\n";
			throw new RuntimeException("No svnUserName and svnUserPassword properties");
		}
		
		//I can't use settings.addAllVariables
		config.flatten().each {
			ivy.settings.setVariable it.key.toString(), it.value.toString()
		}
		
		gcl.getURLs().each {
			ivy.settings.addClasspathURL it;
		}
		
		try {
			ivy.configure(new File(config.ivy.settings));
		} catch (Exception e) {
			e.printStackTrace();
			throw e;
		}
        //ResolveOptions resolveOptions = (new ResolveOptions()).setConfs(['*']).setValidate(true);
        File ivyFile = new File(config.ivy.xml);
        if (!ivyFile.exists()) {
        	println "Can't find $ivyFile";
        	return;
        }
        ResolveReport report = ivy.resolve(ivyFile);
		if (report.hasError()) {
			throw new RuntimeException("Error in retrieve");
		}
		//if (report.)
        ModuleDescriptor md = report.getModuleDescriptor();
        RetrieveOptions options = new RetrieveOptions();
        options.setConfs(md.getConfigurationsNames());
        options.setSync(true);
		
        //open the file for reading - else it is deleted for some magical reason
        ivyFile.withReader {
        	ivy.retrieve(md.getModuleRevisionId(), 'lib/[conf]/[artifact].[ext]', options);
        }
    }
}