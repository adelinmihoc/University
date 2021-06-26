package domain;

import lombok.*;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlType;

/**
 * Client entity
 */
@Getter
@Setter
@NoArgsConstructor(access = AccessLevel.PUBLIC)
@ToString(callSuper = true)
@EqualsAndHashCode(exclude = {"age", "phoneNumber"}, callSuper = true)

@XmlAccessorType(XmlAccessType.PROPERTY)
@XmlType(propOrder = {"firstName", "lastName", "addressId", "age", "phoneNumber"})
public class Client extends BaseEntity<Integer>{

    private String firstName = null;
    private String lastName = null;
    private Integer addressId = null;
    private Integer age = null;
    private String phoneNumber = null;

    @Builder(builderMethodName = "Builder")
    private Client(Integer id, String firstName, String lastName, Integer addressId, Integer age, String phoneNumber) {
        super(id);
        this.firstName = firstName;
        this.lastName = lastName;
        this.age = age;
        this.phoneNumber = phoneNumber;
        this.addressId = addressId;
    }

    @XmlAttribute
    @Override
    public void setId(Integer id) {
        this.id = id;
    }

}
