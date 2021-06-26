package ro.ubb.coffeeshop.model;

import lombok.*;
import org.hibernate.annotations.OnDelete;
import org.hibernate.annotations.OnDeleteAction;

import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.OneToMany;
import java.util.HashSet;
import java.util.Set;

@Getter
@Setter
@NoArgsConstructor(access = AccessLevel.PUBLIC)
@AllArgsConstructor(access = AccessLevel.PUBLIC)
@Builder
@ToString(callSuper = true, exclude = {"customers"})
@EqualsAndHashCode(callSuper=true, exclude = {"customers", "number", "street", "city"})
@Entity
public class Address extends BaseEntity<Integer> {
    private String city;
    private String street;
    private Integer number;

    @Builder.Default
    @OneToMany(cascade = CascadeType.ALL, orphanRemoval = true, fetch = FetchType.EAGER, mappedBy = "address")
    @OnDelete(action = OnDeleteAction.CASCADE)
    private Set<Customer> customers = new HashSet<>();
}
