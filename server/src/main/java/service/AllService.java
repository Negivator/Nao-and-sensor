package service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class AllService {
    @Autowired
    private DemoService demoService;
    @Autowired
    private FamilyService familyService;
    @Autowired
    private UserService userService;
    public DemoService getDemoService() {
        return demoService;
    }

    public FamilyService getFamilyService() {
        return familyService;
    }

    public UserService getUserService() {
        return userService;
    }
}
