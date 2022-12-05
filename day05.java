import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map.Entry;

public class day05 {

    static class Point {
        int x, y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public String toString() {
            return "(" + this.x + "x" + this.y + ")";
        }
    }

    static class Storage extends HashMap<Point, Character> {

        public String toString() {
            StringBuilder builder = new StringBuilder();
            for (Entry<Point, Character> entry : this.entrySet()) {
                builder.append(entry.getKey());
                builder.append(" -> ");
                builder.append(entry.getValue());
                builder.append("\n");
            }
            return builder.toString();
        }
    }

    public day05() {
        List<String> lines = utils.loadFile("inputs/input05_sample.txt");

        HashMap<Point, Character> storage = buildStorage(getLayout(lines));
        System.out.println(storage.toString());
    }

    private HashMap<Point, Character> buildStorage(List<String> lines) {
        HashMap<Point, Character> storage = new HashMap<>();
        for (int iY = 0; iY < lines.size(); iY++) {
            String line = lines.get(iY);
            int x = 0;
            for (int i = 1; i < line.length(); i += 4) {
                char c = line.charAt(i);
                if (c != ' ') {
                    int y = lines.size() - iY;
                    storage.put(new Point(x, y), c);
                }
                x++;
            }
        }
        return storage;
    }

    private List<String> getLayout(List<String> lines) {
        List<String> storage = new ArrayList<String>();
        for (String line : lines) {
            if (line.isEmpty()) {
                break;
            }
            System.out.println(line);
            storage.add(line);
        }
        storage.remove(storage.size() - 1);
        return storage;
    }

    public static void main(String[] args) {
        new day05();
    }
}
