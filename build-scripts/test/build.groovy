def bm = this.class.classLoader.parseClass(new File('scripts/BuildMain.groovy')).inst([] as String[]);
def arg = args.length > 0 ? args[0] : 'package'
switch ( arg ) {
	case "package":
		bm.pack();
		break;
	case "clean":
		bm.clean();
		break;
}