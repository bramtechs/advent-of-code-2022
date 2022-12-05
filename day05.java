import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class day05 {

    static class Storage extends ArrayList<Stack<Character>> {

        public Stack<Character> getOrAdd(int i) {
            if (i < size()) {
                return get(i);
            }
            Stack<Character> stack = new Stack<>();
            add(stack);
            return stack;
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
        List<String> lines = utils.loadFile("inputs/input05.txt");
        List<String> layoutLines = getLayout(lines);
        // layoutLines.forEach((t) -> System.out.println(t));

        Storage firstStorage = buildStorage(layoutLines);
        Storage secondStorage = buildStorage(layoutLines);

        // parse and move crates around
        int[][] commands = getCommands(lines);
        for (int i = 0; i < commands.length; i++) {
            int crates = commands[i][0];
            int source = commands[i][1] - 1;
            int dest = commands[i][2] - 1;

            char[] crateBuffer = new char[crates];

            for (int c = 0; c < crates; c++) {
                char crate = firstStorage.get(source).pop();
                firstStorage.get(dest).push(crate);

                char crate2 = secondStorage.get(source).pop();
                crateBuffer[c] = crate2;
            }

            for (int c = crates - 1; c >= 0; c--) {
                secondStorage.get(dest).push(crateBuffer[c]);
            }
        }

        printStorageTops(firstStorage);
        printStorageTops(secondStorage);
    }

    private void printStorageTops(Storage storage) {
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
        Storage storage = new Storage();
        for (int y = lines.size() - 1; y >= 0; y--) {
            String line = lines.get(y);
            int x = 0;
            for (int i = 1; i < line.length(); i += 4) {
                char c = line.charAt(i);
                if (c != ' ') {
                    storage.getOrAdd(x).push(c);
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
