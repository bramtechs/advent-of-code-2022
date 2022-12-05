import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class day05 {

    static class Storage extends ArrayList<Stack<Character>> {

        public Storage(int cols) {
            for (int i = 0; i < cols; i++) {
                add(new Stack<>());
            }
        }

        public String toString() {
            StringBuilder builder = new StringBuilder();
            for (Stack<Character> stack : this) {
                for (Character ch : stack) {
                    builder.append(" -> ");
                    builder.append(ch);
                }
                builder.append("\n");
            }
            return builder.toString();
        }
    }

    public day05() {
        List<String> lines = utils.loadFile("inputs/input05_sample.txt");

        Storage storage = buildStorage(getLayout(lines));

        // parse and move crates around
        int[][] commands = getCommands(lines);
        for (int i = 0; i < commands.length; i++) {
            int crates = commands[i][0];
            int source = commands[i][1] - 1;
            int dest = commands[i][2] - 1;

            for (int c = 0; c < crates; c++) {
                char crate = storage.get(source).pop();
                storage.get(dest).push(crate);
            }
        }

        // result
        StringBuilder b = new StringBuilder(storage.size());
        for (int i = 0; i < storage.size(); i++) {
            char top = storage.get(i).peek();
            b.append(top);
        }
        System.out.println(b.toString());
    }

    private int[][] getCommands(List<String> lines) {
        // lines from layout already removed
        int[][] cmds = new int[lines.size()][3];
        for (int i = 0; i < lines.size(); i++) {
            String[] segments = lines.get(i).split(" ");
            cmds[i][0] = Integer.parseInt(segments[1].strip());
            cmds[i][1] = Integer.parseInt(segments[3].strip());
            cmds[i][2] = Integer.parseInt(segments[5].strip());
        }
        return cmds;
    }

    private Storage buildStorage(List<String> lines) {
        Storage storage = new Storage(lines.size());
        for (int y = lines.size() - 1; y >= 0; y--) {
            String line = lines.get(y);
            int x = 0;
            for (int i = 1; i < line.length(); i += 4) {
                char c = line.charAt(i);
                if (c != ' ') {
                    storage.get(x).push(c);
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
            storage.add(line);
        }
        lines.removeAll(storage);
        lines.remove(0);

        storage.remove(storage.size() - 1);
        return storage;
    }

    public static void main(String[] args) {
        new day05();
    }
}
