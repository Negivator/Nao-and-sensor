package dao;

import model.Family;
import model.Familyuser;
import org.springframework.stereotype.Repository;

@Repository
public interface FamilyuserMapper {
    int insert(Familyuser record);

    int insertSelective(Familyuser record);
    Familyuser select(Familyuser record);
}