package model;

public class Movie {
    private Integer id;
    private String title;
    private Integer duration;

    public Movie() {

    }

    Integer getId() {
        return this.id;
    }

    String getTitle() {
        return this.title;
    }

    Integer getDuration() {
        return this.duration;
    }

    void setId(Integer id1) {
        this.id = id1;
    }

    void setTitle(String title1) {
        this.title = title1;
    }

    void setDuration(Integer dur) {
        this.duration = dur;
    }

    @Override
    public String toString() {
        return "{\"id\":\"" + id + "\"," +
                "\"title\":\"" + title + "\"," +
                "\"duration\":\"" + duration + "\"}";
    }
}
