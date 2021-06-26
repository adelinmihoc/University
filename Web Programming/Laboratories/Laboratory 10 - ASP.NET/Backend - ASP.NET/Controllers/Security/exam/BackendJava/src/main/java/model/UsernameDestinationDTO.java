package model;

public class UsernameDestinationDTO {
    private String username;
    private String destination;

    public UsernameDestinationDTO() {
    }

    public UsernameDestinationDTO(String username, String destination) {
        this.username = username;
        this.destination = destination;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getDestination() {
        return destination;
    }

    public void setDestination(String destination) {
        this.destination = destination;
    }

    @Override
    public String toString() {
        return "usernameDestinationDTO{" +
                "username='" + username + '\'' +
                ", destination='" + destination + '\'' +
                '}';
    }
}
