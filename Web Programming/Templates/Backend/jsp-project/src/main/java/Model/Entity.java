package Model;

public class Entity {
    public String username;
    public String password;
    public Integer id;
    public String title;
    public String genre;

    @Override
    public String toString() {
        return "{\"username\":\"" + username + "\"," +
                "\"password\":\"" + password + "\"," +
                "\"title\":\"" + title + "\"," +
                "\"genre\":\"" + genre + "\"," +
                "\"id\":\"" + id + "\"}";
    }
}
