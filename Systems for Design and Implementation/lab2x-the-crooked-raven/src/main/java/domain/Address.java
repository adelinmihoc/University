package domain;

import lombok.*;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlType;

/**
 * Address entity
 */

@Getter
@Setter
@NoArgsConstructor(access = AccessLevel.PUBLIC)
@ToString(callSuper = true)
@EqualsAndHashCode(callSuper=true)

@XmlAccessorType(XmlAccessType.PROPERTY)
@XmlType(propOrder = {"city", "street", "number"})
public class Address extends BaseEntity<Integer>{

    private String city = null;
    private String street = null;
    private Integer number = null;

    @Builder(builderMethodName = "Builder")
    private Address(Integer id, String city, String street, Integer number) {
        super(id);
        this.city = city;
        this.street = street;
        this.number = number;
    }

    @XmlAttribute
    @Override
    public void setId(Integer id) {
        this.id = id;
    }
}
