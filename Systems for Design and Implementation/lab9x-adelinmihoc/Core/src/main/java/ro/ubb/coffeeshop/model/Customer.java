package ro.ubb.coffeeshop.model;

import lombok.*;
import org.hibernate.annotations.OnDelete;
import org.hibernate.annotations.OnDeleteAction;

import javax.persistence.*;
import java.util.HashSet;
import java.util.Set;

@Getter
@Setter
@AllArgsConstructor(access = AccessLevel.PUBLIC)
@NoArgsConstructor(access = AccessLevel.PUBLIC)
@Builder
@ToString(callSuper = true, exclude = {"address", "orders"})
@EqualsAndHashCode(exclude = {"age", "lastName", "firstName", "address", "phoneNumber", "orders"}, callSuper = true)
@Entity
public class Customer extends BaseEntity<Integer>{
    private String firstName;
    private String lastName;
    private Integer age;
    private String phoneNumber;

    @ManyToOne(fetch = FetchType.EAGER, optional = false, cascade = CascadeType.MERGE)
    @JoinColumn(name = "address_id")
    private Address address;

    @Builder.Default
    @OneToMany(cascade = CascadeType.ALL, orphanRemoval = true, fetch = FetchType.EAGER, mappedBy = "customer")
    @OnDelete(action = OnDeleteAction.CASCADE)
    private Set<Order> orders = new HashSet<>();
}
