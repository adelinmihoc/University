package ro.ubb.coffeeshop.model;

import lombok.*;

import javax.persistence.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Table(name = "shoporder")
@Getter
@Setter
@NoArgsConstructor(access = AccessLevel.PUBLIC)
@AllArgsConstructor(access = AccessLevel.PUBLIC)
@Builder
@ToString(callSuper = true, exclude = {"orderedCoffees", "customer"})
@EqualsAndHashCode(callSuper = true, exclude = {"orderedCoffees", "customer", "status", "localDateTime"})
@Entity
public class Order extends BaseEntity<Integer> {
    @ManyToOne
    @JoinColumn(name = "customer_id")
    private Customer customer;

    @Builder.Default
    @ManyToMany
    @JoinTable(name = "order_coffees",
                joinColumns = @JoinColumn(name = "order_id"), inverseJoinColumns = @JoinColumn(name = "coffee_id"))
    private List<Coffee> orderedCoffees = new ArrayList<>();

    @Enumerated(EnumType.STRING)
    private Status status;

    private LocalDateTime localDateTime;
}
