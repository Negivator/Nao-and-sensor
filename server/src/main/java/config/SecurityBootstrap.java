package config;

import org.springframework.context.annotation.Configuration;
import org.springframework.security.web.context.AbstractSecurityWebApplicationInitializer;

import javax.servlet.SessionTrackingMode;
import java.util.EnumSet;
import java.util.Set;

/**
 * Created by 12917 on 2017/7/16.
 */
@Configuration
public class SecurityBootstrap extends AbstractSecurityWebApplicationInitializer {
    @Override
    protected boolean enableHttpSessionEventPublisher() {
        return true;
    }

    @Override
    protected Set<SessionTrackingMode> getSessionTrackingModes() {
        return EnumSet.of(SessionTrackingMode.COOKIE);
    }
}
