import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class utils {

    public static <T> void check(T input, T shouldEqual) {
        if (input != shouldEqual) {
            throw new RuntimeException("Assertion failed: value was " + input);
        }
    }

    public static List<String> loadFile(String fileName) {
        FileReader reader;
        try {
            reader = new FileReader(fileName);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            System.err.println("Could not find file at " + fileName);
            return null;
        }
        int i;

        List<String> lines = new ArrayList<String>();
        StringBuilder builder = new StringBuilder();
        try {
            while ((i = reader.read()) != -1) {
                char c = (char) i;
                if (c == '\n') {
                    lines.add(builder.toString());
                    builder = new StringBuilder();
                } else if (c != '\r') {
                    builder.append(c);
                }
            }
        } catch (IOException exc) {
            exc.printStackTrace();
            System.err.println("IO error occured while reading " + fileName);
            return null;
        }

        try {
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.err.println("Could not correctly close " + fileName);
        }
        return lines;
    }
}