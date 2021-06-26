package domain.Adapters;

import javax.xml.bind.annotation.adapters.XmlAdapter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class DateFormatAdapter extends XmlAdapter<String, LocalDateTime> {
    private final DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd/HH:mm:ss");

    @Override
    public LocalDateTime unmarshal(String dateTime) {
        return !dateTime.equals("") ? LocalDateTime.parse(dateTime, dateTimeFormatter) : null;
    }

    @Override
    public String marshal(LocalDateTime dateTime) {
        return dateTime.format(dateTimeFormatter);
    }
}
