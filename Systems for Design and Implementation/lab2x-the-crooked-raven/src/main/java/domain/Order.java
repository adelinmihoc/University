package domain;

import domain.Adapters.AttributeAdapter;
import domain.Adapters.DateFormatAdapter;
import lombok.*;
import org.apache.commons.lang3.tuple.Pair;
import javax.xml.bind.annotation.*;
import javax.xml.bind.annotation.adapters.XmlJavaTypeAdapter;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

/**
 * Order Entity
 */
@Getter
@Setter
@NoArgsConstructor(access = AccessLevel.PUBLIC)
@ToString(callSuper = true)
@EqualsAndHashCode(exclude = {"status", "time"}, callSuper = true)

@XmlAccessorType(XmlAccessType.PROPERTY)
@XmlType(propOrder = {"id", "status", "time", "coffeesId"})
public class Order extends BaseEntity<Pair<Integer, Integer>> {

    @XmlElementWrapper(name = "coffeesId")
    @XmlElement(name = "cId")
    private List<Integer> coffeesId = new ArrayList<>();
    private Status status = null;

    @XmlJavaTypeAdapter(DateFormatAdapter.class)
    private LocalDateTime time = null;

    @Builder(builderMethodName = "Builder")
    private Order(Pair<Integer, Integer> id, Status status, LocalDateTime time) {
        super(id);
        this.status = status;
        this.time = time;
    }

    @Override
    @XmlJavaTypeAdapter(value = AttributeAdapter.class)
    public void setId(Pair<Integer, Integer> id) {
        this.id = id;
    }

    @Override
    @XmlJavaTypeAdapter(value = AttributeAdapter.class)
    public Pair<Integer, Integer> getId() {
        return this.id;
    }

}
