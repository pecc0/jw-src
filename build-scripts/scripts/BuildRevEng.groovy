import org.apache.tools.ant.Project;
import org.hibernate.tool.ant.Hbm2JavaExporterTask;
import org.hibernate.tool.ant.HibernateToolTask;
import org.hibernate.tool.ant.JDBCConfigurationTask;

import groovy.util.ConfigObject;


class BuildRevEng {
	public void run(ConfigObject config) {
		Project project = new Project();
		HibernateToolTask htt = new HibernateToolTask();
		JDBCConfigurationTask jdbcConf = htt.createJDBCConfiguration();
		jdbcConf.setConfigurationFile(new File('hibernate/hibernate.cfg.xml'));
		Hbm2JavaExporterTask hbm2Java = htt.createHbm2Java();
		hbm2Java.setEjb3(true);
		htt.setDestDir(new File('hibernate/generated'));
		htt.setProject project;
		
		try {
			htt.execute();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
