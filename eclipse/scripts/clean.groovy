def bm = this.class.classLoader.parseClass(new File('build-scripts/BuildMain.groovy')).inst(['build-scripts'] as String[])
bm.clean()