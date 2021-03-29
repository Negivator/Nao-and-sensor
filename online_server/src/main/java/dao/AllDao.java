package dao;

import model.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

@Repository
public class AllDao {
    @Autowired
    private DemoMapper demoMapper;
    @Autowired
    private FamilyMapper familyMapper;
    @Autowired
    private FamilyuserMapper familyuserMapper;
    @Autowired
    private FcommondMapper fcommondMapper;
    @Autowired
    private FinfoMapper finfoMapper;
    @Autowired
    private UserMapper userMapper;
    @Autowired
    private UserpermissionMapper userpermissionMapper;
    @Autowired
    private  FpicMapper fpicMapper;
    public DemoMapper getDemoMapper() {
        return demoMapper;
    }

    public FamilyMapper getFamilyMapper() {
        return familyMapper;
    }

    public UserMapper getUserMapper() {
        return userMapper;
    }

    public FamilyuserMapper getFamilyuserMapper() {
        return familyuserMapper;
    }

    public FcommondMapper getFcommondMapper() {
        return fcommondMapper;
    }

    public FinfoMapper getFinfoMapper() {
        return finfoMapper;
    }

    public UserpermissionMapper getUserpermissionMapper() {
        return userpermissionMapper;
    }

    public FpicMapper getFpicMapper() {
        return fpicMapper;
    }
}
