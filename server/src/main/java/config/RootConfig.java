package config;

import org.springframework.aop.interceptor.AsyncUncaughtExceptionHandler;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.FilterType;
import org.springframework.context.annotation.Import;
import org.springframework.scheduling.annotation.AsyncConfigurer;
import org.springframework.scheduling.annotation.SchedulingConfigurer;
import org.springframework.scheduling.config.ScheduledTaskRegistrar;
import org.springframework.transaction.PlatformTransactionManager;
import org.springframework.transaction.annotation.TransactionManagementConfigurer;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;

import java.util.concurrent.Executor;

@Configuration
@ComponentScan(basePackages = {"config"},
    excludeFilters = {@ComponentScan.Filter(type = FilterType.ANNOTATION,value = {EnableWebMvc.class, ControllerAdvice.class})})
@Import({SecurityConfig.class})
public class RootConfig implements AsyncConfigurer,SchedulingConfigurer,TransactionManagementConfigurer {

    @Override
    public void configureTasks(ScheduledTaskRegistrar taskRegistrar) {

    }

    @Override
    public AsyncUncaughtExceptionHandler getAsyncUncaughtExceptionHandler() {
        return null;
    }

    @Override
    public PlatformTransactionManager annotationDrivenTransactionManager() {
        return null;
    }

    @Override
    public Executor getAsyncExecutor() {
        return null;
    }
}
