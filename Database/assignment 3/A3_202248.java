import java.security.SecureRandom;
import java.sql.*;
import java.util.*;

public class A3_202248 {

    public static void main(String[] args) {
        A3_202248 script = new A3_202248();
    }

    private int NUMERORECORD = 1000000;

    public A3_202248() {
        String url = "jdbc:postgresql://sci-didattica.unitn.it/db_225";
        Properties props = new Properties();
        props.setProperty("user", "db_225");
        props.setProperty("password", "datagayz");
        props.setProperty("ssl", "false");
        Connection connection = null;

        try {
            connection = DriverManager.getConnection(url, props);
        } catch (Exception e) {
            //System.exit(0);
        }

        task1(connection);
        task2(connection);
        task3(connection);
        task4(connection);
        task5(connection);
        task6(connection);
        task7(connection);
        task8(connection);
        task9(connection);
        task10(connection);
        task11(connection);

        try {
            connection.close();
        } catch (SQLException e) {
        }
    }

    private String drop1 = "DROP TABLE IF EXISTS \"Professor\", \"Course\" cascade;";

    public void task1(Connection connection) {
        long startTime = System.nanoTime();
        try {
            PreparedStatement ps = connection.prepareCall(drop1);
            ps.executeUpdate();
            ps.close();
        } catch (SQLException e) {
        }
        long stopTime = System.nanoTime();
        long elapsedTime = stopTime - startTime;
        System.out.println("Step 1 needs " + elapsedTime + " ns");
    }

    private String query1 = "CREATE TABLE \"Professor\" (id int NOT NULL,"
            + " name varchar (50) NOT NULL,"
            + " address varchar (50) NOT NULL,"
            + " age int NOT NULL,"
            + " height float NOT NULL,"
            + " PRIMARY KEY (id));";
    private String query2 = "CREATE TABLE \"Course\" (cid varchar (25) NOT NULL,"
            + " title varchar (50) NOT NULL,"
            + " area varchar (30) NOT NULL,"
            + " instructor int NOT NULL,"
            + " PRIMARY KEY (cid),"
            + " FOREIGN KEY (instructor) REFERENCES \"Professor\");";

    public void task2(Connection connection) {
        long startTime = System.nanoTime();
        try {
            PreparedStatement ps = connection.prepareStatement(query1);
            ps.executeUpdate();
            //ps.close();
            ps = connection.prepareStatement(query2);
            ps.executeUpdate();
            ps.close();
        } catch (SQLException e) {
        }
        long stopTime = System.nanoTime();
        long elapsedTime = stopTime - startTime;
        System.out.println("Step 2 needs " + elapsedTime + " ns");
    }

    private String query3 = "INSERT INTO \"Professor\" (id, name, address, age, height) VALUES (?, ?, ?, ?, ?)";
    private ArrayList<Integer> IDs;

    public void task3(Connection connection) {                                       //missing rest of values of tuples
        long startTime = System.nanoTime();
        try {
            Set set = new HashSet();
            IDs = new ArrayList<Integer>();                  //needed?
            float height;
            int id = 0;
            PreparedStatement ps = connection.prepareStatement(query3);
            ps.clearParameters();
            while (set.size() < NUMERORECORD) {                                      //table has less than 1 mil tuples   //number??
                height = (new Random().nextFloat() * 50) + 160;
                if (height != 185.00) {
                    set.add(height);
                }
                if (id < (NUMERORECORD - 1)) {                                         //number??
                    IDs.add(id++);
                }
            }
            IDs.add(id);
            Collections.shuffle(IDs);
            Iterator<Float> i = set.iterator();
            int j = 0;
            while (i.hasNext() && j < (NUMERORECORD - 1)) {                                     //number??
                height = i.next();
                ps.setInt(1, IDs.get(j++));
                ps.setString(2, generateString(40));
                ps.setString(3, generateString(40));
                ps.setInt(4, (new Random().nextInt(60) + 18));
                ps.setFloat(5, height);                                         //name address, age, id
                ps.addBatch();
                if (j % 10000 == 0) {
                    ps.executeBatch();
                    ps.clearBatch();
                    System.gc();
                }
            }
            height = (float) 185.00;
            ps.setInt(1, IDs.get(j));
            ps.setString(2, generateString(40));
            ps.setString(3, generateString(40));
            ps.setInt(4, (new Random().nextInt(60) + 18));
            ps.setFloat(5, height);
            ps.addBatch();
            ps.executeBatch();
            ps.close();
        } catch (SQLException e) {
        }
        long stopTime = System.nanoTime();
        long elapsedTime = stopTime - startTime;
        System.out.println("Step 3 needs " + elapsedTime + " ns");
    }

    public String generateString(int count) {
        String ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_";
        SecureRandom RANDOM = new SecureRandom();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < count; ++i) {
            sb.append(ALPHABET.charAt(RANDOM.nextInt(ALPHABET.length())));
        }
        return sb.toString();
    }

    private String query4 = "INSERT INTO \"Course\" (cid, title, area, instructor) VALUES (?, ?, ?, ?)";

    public void task4(Connection connection) {
        long startTime = System.nanoTime();
        try {
            Set set = new HashSet();
            String cid;
            PreparedStatement ps = connection.prepareStatement(query4);
            ps.clearParameters();
            while (set.size() < NUMERORECORD) {                                      //table has less than 1 mil tuples
                cid = generateString(20);                                       //number??
                set.add(cid);
            }
            Iterator<String> i = set.iterator();
            Collections.shuffle(IDs);
            int instructor = 0;
            while (i.hasNext()) {
                cid = i.next();
                ps.setString(1, cid);
                ps.setString(2, generateString(49));
                ps.setString(3, generateString(29));                            //string (25), STRING (50), STRING (30), int
                ps.setInt(4, IDs.get(instructor++));                                     //name address, age, id
                ps.addBatch();
                if (instructor % 10000 == 0) {
                    ps.executeBatch();
                    ps.clearBatch();
                    System.gc();
                }
            }
            ps.executeBatch();
            ps.clearBatch();
            ps.close();
            System.gc();
        } catch (SQLException e) {
        }
        long stopTime = System.nanoTime();
        long elapsedTime = stopTime - startTime;
        System.out.println("Step 4 needs " + elapsedTime + " ns");
    }
    private String query5 = "SELECT id FROM \"Professor\";";

    public void task5(Connection connection) {
        long startTime = System.nanoTime();
        try {
            PreparedStatement ps = connection.prepareStatement(query5);
            //ps.clearParameters();
            ResultSet resultSet = ps.executeQuery();
            while (resultSet.next()) {
                System.err.println(resultSet.getInt("id"));
            }
            ps.close();
        } catch (SQLException e) {
        }
        long stopTime = System.nanoTime();
        long elapsedTime = stopTime - startTime;
        System.out.println("Step 5 needs " + elapsedTime + " ns");
    }

    private String query6 = "UPDATE \"Professor\" SET height = 200 WHERE height = 185;";

    public void task6(Connection connection) {
        long startTime = System.nanoTime();
        try {
            PreparedStatement ps = connection.prepareStatement(query6);
            ps.executeUpdate();
            ps.close();
        } catch (SQLException e) {
        }
        long stopTime = System.nanoTime();
        long elapsedTime = stopTime - startTime;
        System.out.println("Step 6 needs " + elapsedTime + " ns");
    }

    private String query7 = "SELECT id, address FROM \"Professor\" WHERE height = 200;";

    public void task7(Connection connection) {
        long startTime = System.nanoTime();
        try {
            PreparedStatement ps = connection.prepareStatement(query7);
            ResultSet resultSet = ps.executeQuery();
            while (resultSet.next()) {
                System.err.println(resultSet.getInt("id"));
                System.err.println(resultSet.getString("address"));
            }
            resultSet.close();
            ps.close();
        } catch (SQLException e) {
        }
        long stopTime = System.nanoTime();
        long elapsedTime = stopTime - startTime;
        System.out.println("Step 7 needs " + elapsedTime + " ns");
    }
    private String query8 = "CREATE INDEX indice ON \"Professor\" (height);";

    public void task8(Connection connection) {
        long startTime = System.nanoTime();
        try {
            PreparedStatement ps = connection.prepareStatement(query8);
            ps.executeUpdate();
            ps.close();
        } catch (SQLException e) {
        }
        long stopTime = System.nanoTime();
        long elapsedTime = stopTime - startTime;
        System.out.println("Step 8 needs " + elapsedTime + " ns");
    }
    private String query9 = "SELECT id FROM \"Professor\";";

    public void task9(Connection connection) {
        long startTime = System.nanoTime();
        try {
            PreparedStatement ps = connection.prepareStatement(query9);
            ResultSet resultSet = ps.executeQuery();
            while (resultSet.next()) {
                System.err.println(resultSet.getInt("id"));
            }
        } catch (SQLException e) {
        }
        long stopTime = System.nanoTime();
        long elapsedTime = stopTime - startTime;
        System.out.println("Step 9 needs " + elapsedTime + " ns");
    }

    private String query10 = "UPDATE \"Professor\" SET height = 210 WHERE height = 200;";             //to check

    public void task10(Connection connection) {
        long startTime = System.nanoTime();
        try {
            PreparedStatement ps = connection.prepareStatement(query10);
            ps.executeUpdate();
            ps.close();
        } catch (SQLException e) {
        }
        long stopTime = System.nanoTime();
        long elapsedTime = stopTime - startTime;
        System.out.println("Step 10 needs " + elapsedTime + " ns");
    }

    private String query11 = "SELECT id, address FROM \"Professor\" WHERE height = 210;";

    public void task11(Connection connection) {
        long startTime = System.nanoTime();
        try {
            PreparedStatement ps = connection.prepareStatement(query11);
            ResultSet resultSet = ps.executeQuery();
            while (resultSet.next()) {
                System.err.println(resultSet.getInt("id"));
                System.err.println(resultSet.getString("address"));
            }
            resultSet.close();
            ps.close();
        } catch (SQLException e) {
        }
        long stopTime = System.nanoTime();
        long elapsedTime = stopTime - startTime;
        System.out.println("Step 11 needs " + elapsedTime + " ns");
    }
}
