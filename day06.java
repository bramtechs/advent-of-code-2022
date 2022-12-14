import java.util.List;

public class day06 {
    public static class Signal {
        private String content;

        public Signal(String content) {
            this.content = content;
        }

        boolean isSpecial(String packet) {
            for (int i = 0; i < packet.length(); i++) {
                for (int j = 0; j < packet.length(); j++) {
                    if (i == j)
                        continue;

                    if (packet.charAt(i) == packet.charAt(j)) {
                        return false;
                    }
                }
            }
            return true;
        }

        // go forwards and look back
        int getStartIndex(int size) {
            for (int i = size; i < content.length(); i++) {
                String packet = content.substring(i - size, i);
                if (isSpecial(packet)) {
                    return i;
                }
            }
            return 0;
        }
    }

    private String[] examples = new String[] {
            "mjqjpqmgbljsphdztnvjfqwrcgsmlb",
            "bvwbjplbgvbhsrlpgdmjqwftvncz",
            "nppdvjthqldpwncqszvftbrmjlhg",
            "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",
            "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"
    };

    void calculateExamples(int size) {
        for (String example : examples) {
            Signal sign = new Signal(example);
            System.out.println(sign.getStartIndex(size));
        }
    }

    public day06() {
        List<String> lines = utils.loadFile("inputs/input06.txt");
        utils.check(lines.size(), 1);

        Signal signal = new Signal(lines.get(0));
        System.out.println(signal.getStartIndex(4));
        System.out.println(signal.getStartIndex(14));
    }

    public static void main(String[] args) {
        new day06();
        // new day06().calculateExamples(4);
        // new day06().calculateExamples(14);
    }
}
