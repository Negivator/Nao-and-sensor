package controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import service.AllService;

@Controller
public class BaseAction {

    @Autowired
    private AllService allService;

    public AllService getAllService() {
        return allService;
    }
//    设置首页
    @RequestMapping(value = "/")
    public final String index(){
        return "public/index";
    }
}
