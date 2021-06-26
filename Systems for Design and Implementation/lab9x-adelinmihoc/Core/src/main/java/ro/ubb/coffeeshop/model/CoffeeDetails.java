package ro.ubb.coffeeshop.model;

import lombok.*;

import javax.persistence.Embeddable;

@Getter
@Setter
@NoArgsConstructor(access = AccessLevel.PUBLIC)
@AllArgsConstructor(access = AccessLevel.PUBLIC)
@Builder
@ToString
@EqualsAndHashCode
@Embeddable
public class CoffeeDetails{
    private String origin;
    private Integer quantity;
    private Integer price;
}
