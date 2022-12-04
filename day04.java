import java.util.List;

public class day04 {

    static class Pair {
        private int[] start = new int[2];
        private int[] end = new int[2];

        public Pair(String line) {
            String[] partners = line.split(",");
            utils.check(partners.length, 2);

            for (int i = 0; i < 2; i++) {
                String[] numbers = partners[i].split("-");
                utils.check(numbers.length, 2);
                start[i] = Integer.valueOf(numbers[0]);
                end[i] = Integer.valueOf(numbers[1]);
            }
        }

        public boolean containsPartner() {
            if (start[1] >= start[0] && end[1] <= end[0]) {
                return true;
            }
            if (start[0] >= start[1] && end[0] <= end[1]) {
                return true;
            }
            return false;
        }

        public boolean overlapsPartner() {
            return !(start[1] > end[0] || start[0] > end[1]);
        }

        public String toString() {
            return start[0] + "-" + end[0] + "," + start[1] + "-" + end[1];
        }
    }

    public static void main(String[] args) {

        List<String> lines = utils.loadFile("inputs/input04.txt");

        Pair[] pairs = new Pair[lines.size()];

        int containing = 0;
        int overlaps = 0;
        for (int i = 0; i < lines.size(); i++) {
            Pair pair = pairs[i] = new Pair(lines.get(i));
            if (pair.containsPartner()) {
                containing++;
            }
            if (pair.overlapsPartner()) {
                overlaps++;
            }
        }
        System.out.println(containing);
        System.out.println(overlaps);
    }
}