package domain.Adapters;

import org.apache.commons.lang3.tuple.ImmutablePair;
import org.apache.commons.lang3.tuple.Pair;
import javax.xml.bind.annotation.adapters.XmlAdapter;
import java.util.Arrays;
import java.util.List;

public class AttributeAdapter extends XmlAdapter<String, Pair<Integer, Integer>> {
    @Override
    public Pair<Integer, Integer> unmarshal(String v) {
        List<String> leftRight = Arrays.asList(v.split(", "));
        return new ImmutablePair<>(Integer.parseInt(leftRight.get(0)), Integer.parseInt(leftRight.get(1)));
    }

    @Override
    public String marshal(Pair<Integer, Integer> v) {
        return v.getLeft().toString() + ", " + v.getRight().toString();
    }
}
