import { Component } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferService, AuthenticationInfo } from './../../shared/sniffer/index';

@Component({
  moduleId: module.id,
  selector: 'session-subscription',
  templateUrl: 'session-subscription.component.html'
})
export class SessionSubscriptionComponent {

  public authenticationInfo: AuthenticationInfo = null;

  constructor(private router: Router, private snifferService: SnifferService) {
    this.snifferService.authenticationInfo
      .subscribe((authInfo : AuthenticationInfo) => {
        if (authInfo.isAuthenticated) {
          this.router.navigate(['capture']);
        } else {
          this.authenticationInfo = authInfo;
        }
      });
  }

  public subscribeClicked(password: string) : void {
    this.snifferService.sendAuthenticate(password);
  }

}
