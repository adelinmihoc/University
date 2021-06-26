package raven.iss.web.security.permissions;

import org.springframework.security.access.prepost.PreAuthorize;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Retention(RetentionPolicy.RUNTIME)
@PreAuthorize("hasAuthority('PCMEMBER') and @customAuthenticationManager.pcMemberConferenceIdMatches(authentication," +
        "#cid)")
public @interface PCMemberPermission {
}
