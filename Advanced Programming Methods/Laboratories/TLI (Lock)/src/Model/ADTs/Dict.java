package Model.ADTs;

import java.util.HashMap;


public class Dict<T1, T2> implements IDict<T1, T2> {

    HashMap<T1,T2> dictionary;

    public Dict() {
        dictionary = new HashMap<>();
    }

    public Dict(HashMap<T1, T2> content) {
        dictionary = content;
    }

    @Override
    public String toString() {
        return dictionary.toString();
    }

    @Override
    public void remove(T1 id) {
        dictionary.remove(id);
    }

    @Override
    public HashMap<T1, T2> getContent() {
        return dictionary;
    }

    @Override
    public void setContent(HashMap<T1, T2> content) {
        this.dictionary = content;
    }

    @Override
    public IDict<T1, T2> Iclone() {
        HashMap<T1, T2> newHM = new HashMap<>(dictionary);
        Dict<T1, T2> newDict = new Dict<>();
        newDict.setContent(newHM);
        return newDict;
    }

    @Override
    public T1 getFirst() {
        return null;
    }

    @Override
    public void add(T1 v1, T2 v2) {
        dictionary.put(v1,v2);
    }

    @Override
    public void update(T1 v1, T2 v2) {
        dictionary.replace(v1,v2);
    }

    @Override
    public T2 lookup(T1 id) {
        return dictionary.get(id);
    }

    @Override
    public boolean isDefined(T1 id) {
        return this.lookup(id) != null;
    }


}

