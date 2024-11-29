package com.elsys.di_oc.controller;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HelloWorldController {
    @Value("${person.name}")
    private String name;

    @GetMapping("/hello")
    public String hello(){
        return "Hello, World, " + name;
    }
}
