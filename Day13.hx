import haxe.display.Server.ConfigureParams;
import haxe.ds.IntMap;

class Day13 {
	private function orderPacket(first, second) {}

	private function parseSegment(line:String, packet:Array<Array<Int>>) {
		// TODO
	}

	private function parsePacket(first:String, second:String) {
		Sys.println(first);
		Sys.println(second);
	}

	private function new() {
		var lines = Utils.readInput("inputs/input13_sample.txt");
		var i:Int = 0;
		while (i < lines.length) {
			var first = lines[i++];
			var second = lines[i++];
			parsePacket(first, second);
			i++;
		}
	}

	static function main() {
		new Day13();
	}
}
