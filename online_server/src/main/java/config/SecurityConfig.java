package config;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.builders.WebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.config.annotation.web.servlet.configuration.EnableWebMvcSecurity;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

import javax.sql.DataSource;

@Configuration
@EnableWebMvcSecurity
@ComponentScan
public class SecurityConfig extends WebSecurityConfigurerAdapter {

    @Autowired
    private DataSource dataSource;
    @Override
    protected void configure(AuthenticationManagerBuilder auth) throws Exception {
//        auth.inMemoryAuthentication()
//                .withUser("John")
//                .password("password")
//                .authorities("USER")
//                .and()
//                    .withUser("Margaret")
//                    .password("green")
//                    .authorities("USER","ADMIN");
        auth.jdbcAuthentication()
                .dataSource(this.dataSource)
                .usersByUsernameQuery("SELECT username,password,enable FROM User WHERE username=?")
                .authoritiesByUsernameQuery("SELECT username,permission FROM UserPermission WHERE username=?")
                .passwordEncoder(new BCryptPasswordEncoder());


    }

    @Override
    public void configure(WebSecurity web) throws Exception {
        web.ignoring().antMatchers("/jsp/**");
    }

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http
                .authorizeRequests()
                .antMatchers("/","/family/**","/public/**","/user/register").permitAll()
                .antMatchers("/user/**").hasAuthority("user")
                .anyRequest().authenticated()
                .and().formLogin()
                .loginPage("/user/login")
                .defaultSuccessUrl("/user/loginsuccess")
                .failureForwardUrl("/user/loginfail")
                .usernameParameter("name")
                .passwordParameter("pass")
                .permitAll()
                .and().logout()
                .logoutUrl("/user/logout").logoutSuccessUrl("/user/loginsuccess")
                .invalidateHttpSession(true).deleteCookies("JSESSIONID")
                .permitAll()
                .and().sessionManagement()
                .sessionFixation().changeSessionId()
                .maximumSessions(1).maxSessionsPreventsLogin(false).and().and()
             .csrf().disable();

    }



}

