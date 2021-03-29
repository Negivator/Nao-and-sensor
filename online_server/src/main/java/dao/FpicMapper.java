package dao;

import model.Fpic;
import org.springframework.stereotype.Repository;

@Repository
public interface FpicMapper {
    int insert(Fpic record);

    int insertSelective(Fpic record);
    Fpic select(Fpic record);
}