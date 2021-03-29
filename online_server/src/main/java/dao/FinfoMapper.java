package dao;

import model.Finfo;
import org.springframework.stereotype.Repository;

@Repository
public interface FinfoMapper {
    int insert(Finfo record);

    int insertSelective(Finfo record);
    Finfo select(Finfo record);
    int update(Finfo record);
}