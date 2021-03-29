package controller;

import model.Demo;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import service.AllService;

import java.util.List;

@ControllerAdvice
@RequestMapping(value = "/demo")
public class DemoAction extends BaseAction {
    @RequestMapping(value = "/demo")
    @ResponseBody
    public List<Demo> demo(){
        return getAllService().getDemoService().getList();
    }

}
