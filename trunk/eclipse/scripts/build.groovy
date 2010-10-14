def bm = this.class.classLoader.parseClass(new File('build-scripts/BuildMain.groovy')).inst(['build-scripts'] as String[])
bm.init()
bm.ivy()
bm.reveng()

println 'complete'