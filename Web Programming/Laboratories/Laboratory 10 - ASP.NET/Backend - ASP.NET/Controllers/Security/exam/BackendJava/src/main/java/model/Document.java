package model;

public class Document {
    private Integer id;
    private String name;
    private String contents;

    public Document() {
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getContents() {
        return contents;
    }

    public void setContents(String contents) {
        this.contents = contents;
    }

    @Override
    public String toString() {
        return "{\"id\":\"" + id + "\"," +
                "\"name\":\"" + name + "\"," +
                "\"contents\":\"" + contents + "\"}";
    }
}
