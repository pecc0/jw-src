import org.apache.ivy.core.module.descriptor.ModuleDescriptor;
import org.apache.ivy.core.report.ResolveReport;
import org.apache.ivy.Ivy;
import org.apache.ivy.core.resolve.ResolveOptions;
import org.apache.ivy.core.retrieve.RetrieveOptions;

class BuildIvy {
    	
    public void run(ConfigObject config) {
    
        Ivy ivy = Ivy.newInstance();
        ivy.configure(new File(config.ivy.settings));
        //ResolveOptions resolveOptions = (new ResolveOptions()).setConfs(['*']).setValidate(true);
        File ivyFile = new File(config.ivy.xml);
        if (!ivyFile.exists()) {
        	println "Can't find $ivyFile";
        	return;
        }
        ResolveReport report = ivy.resolve(ivyFile);
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