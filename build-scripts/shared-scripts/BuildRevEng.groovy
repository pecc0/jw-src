import org.apache.tools.ant.Project;
import org.apache.tools.ant.types.Path;
import org.apache.tools.ant.types.PropertySet;
import org.hibernate.tool.ant.Hbm2JavaExporterTask;
import org.hibernate.tool.ant.HibernateToolTask;
import org.hibernate.tool.ant.JDBCConfigurationTask;

import groovy.util.ConfigObject;


class BuildRevEng {
	public void run(ConfigObject config, main) {
		this.class.classLoader.addClasspath(config.scriptsRoot); //for log4j.properties
		
		if (!config.flatten().containsKey('hibernate.connection.password')) {
			println "Please, add your hibernate.connection.password in local.build.conf: \n" +
					"  hibernate.connection.password='the pass'\n"
			throw new RuntimeException("No hibernate.connection.password properties");
		}
		
		PropertySet ps = new PropertySet() {
			public java.util.Properties getProperties() {
				return config.toProperties();
			};
		}
		
		Project project = new Project();
		HibernateToolTask htt = new HibernateToolTask();
		
		JDBCConfigurationTask jdbcConf = new JDBCConfigurationTask() {
			protected java.util.Properties getProperties() {
				return config.toProperties();
			};		
		}
		jdbcConf.setConfigurationFile(new File(config.reveng.hibernate.cfg.xml));
		jdbcConf.setRevEngFile(new Path(project, config.reveng.hibernate.revengxml))
		
		jdbcConf.setPackageName config.reveng.hibernate.packagename;
		
		//I'm so glad that I use groovy
		htt.configurationTask = jdbcConf;
		
		Hbm2JavaExporterTask hbm2Java = htt.createHbm2Java();
		hbm2Java.setEjb3(true);
		
		hbm2Java.addConfiguredPropertySet(ps)
		htt.setDestDir(new File(config.reveng.dest.dir));
		htt.setProject project;
		
		try {
			htt.execute();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
