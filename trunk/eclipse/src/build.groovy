import org.apache.ivy.core.module.descriptor.ModuleDescriptor;
import org.apache.ivy.core.report.ResolveReport;
import org.apache.ivy.Ivy;
import org.apache.ivy.core.resolve.ResolveOptions;
import org.apache.ivy.core.retrieve.RetrieveOptions;


Ivy ivy = Ivy.newInstance();
ivy.configure(new File('build-external/ivysettings.xml'))
//ResolveOptions resolveOptions = (new ResolveOptions()).setConfs(['*']).setValidate(true);
ResolveReport report = ivy.resolve(new File('lib/ivy.xml'));
ModuleDescriptor md = report.getModuleDescriptor();
RetrieveOptions options = new RetrieveOptions();
options.setConfs(md.getConfigurationsNames());
options.setSync true;

ivy.retrieve(md.getModuleRevisionId(), 'lib/[conf]/[artifact].[ext]', options);
println 'complete'