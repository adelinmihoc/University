package domain;

import lombok.*;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlType;

/**
 * Coffee Entity
 */
@Getter
@Setter
@NoArgsConstructor(access = AccessLevel.PUBLIC)
@ToString(callSuper = true)
@EqualsAndHashCode(exclude = {"quantity", "price"}, callSuper = true)

@XmlAccessorType(XmlAccessType.PROPERTY)
@XmlType(propOrder = {"name", "origin", "quantity", "price"})
public class Coffee extends BaseEntity<Integer> {

    private String name = null;
    private String origin = null;
    private Integer quantity = null;
    private Integer price = null;

    @Builder(builderMethodName = "Builder")
    private Coffee(Integer id, String name, String origin, Integer quantity, Integer price) {
        super(id);
        this.name = name;
        this.origin = origin;
        this.quantity = quantity;
        this.price = price;
    }

    @XmlAttribute
    @Override
    public void setId(Integer id) {
        this.id = id;
    }

}