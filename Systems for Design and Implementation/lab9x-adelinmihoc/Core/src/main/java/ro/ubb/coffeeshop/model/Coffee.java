package ro.ubb.coffeeshop.model;

import lombok.*;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Getter
@Setter
@NoArgsConstructor(access = AccessLevel.PUBLIC)
@AllArgsConstructor(access = AccessLevel.PUBLIC)
@Builder
@ToString(callSuper = true, exclude = {"orders"})
@EqualsAndHashCode(exclude = {"orders", "name", "details"}, callSuper = true)
@Entity
public class Coffee extends BaseEntity<Integer> {
    private String name;

    @Builder.Default
    @Embedded
    private CoffeeDetails details = new CoffeeDetails();

    @Builder.Default
    @ManyToMany(mappedBy = "orderedCoffees")
    private List<Order> orders = new ArrayList<>();

    public String getOrigin() {
        return this.details.getOrigin();
    }

    public Integer getQuantity() {
        return this.details.getQuantity();
    }

    public Integer getPrice() {
        return this.details.getPrice();
    }

    public void setOrigin(String origin) {
        this.details.setOrigin(origin);
    }

    public void setQuantity(Integer quantity) {
        this.details.setQuantity(quantity);
    }

    public void setPrice(Integer price) {
        this.details.setPrice(price);
    }
}
