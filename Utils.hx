class Utils {
	static public function readInput(fileName) {
		var fin = sys.io.File.read(fileName, false);
		var lines = [];
		while (true) {
			try {
				lines.push(fin.readLine());
			} catch (e:haxe.io.Eof) {
				fin.close();
				break;
			}
		}
		return lines;
	}
}
