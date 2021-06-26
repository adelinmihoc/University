package model;

public class VacationDestination {
    private Integer id;
    private String destination;
    private String country;
    private Integer price;

    public VacationDestination() {
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getDestination() {
        return destination;
    }

    public void setDestination(String destination) {
        this.destination = destination;
    }

    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public Integer getPrice() {
        return price;
    }

    public void setPrice(Integer price) {
        this.price = price;
    }

    @Override
    public String toString() {
        return "{\"id\":\"" + id + "\"," +
                "\"destination\":\"" + destination + "\"," +
                "\"country\":\"" + country + "\"," +
                "\"price\":\"" + price + "\"}";
    }
}
