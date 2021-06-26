package model;

import java.util.Arrays;

public class Post {
    private Integer id;
    private Integer user_id;
    private byte[] image;
    private Integer votes;
    private String base64Image;

    public Post() {
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getUser_id() {
        return user_id;
    }

    public void setUser_id(Integer user_id) {
        this.user_id = user_id;
    }

    public byte[] getImage() {
        return image;
    }

    public void setImage(byte[] image) {
        this.image = image;
    }

    public Integer getVotes() {
        return votes;
    }

    public void setVotes(Integer votes) {
        this.votes = votes;
    }

    public String getBase64Image() {
        return base64Image;
    }

    public void setBase64Image(String base64Image) {
        this.base64Image = base64Image;
    }

    @Override
    public String toString() {
        return "Post{" +
                "id=" + id +
                ", user_id=" + user_id +
                ", image=" + Arrays.toString(image) +
                ", votes=" + votes +
                ", base64Image='" + base64Image + '\'' +
                '}';
    }


}
