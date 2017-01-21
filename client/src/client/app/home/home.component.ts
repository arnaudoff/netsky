import { Component } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferService, HostInfo, AuthenticationInfo }
from './../shared/sniffer/index';

@Component({
  moduleId: module.id,
  selector: 'home',
  templateUrl: 'home.component.html',
  styleUrls: ['home.component.css'],
})
export class HomeComponent {
  private hostInfo: HostInfo;
  private authenticationInfo: AuthenticationInfo;

  constructor(private router: Router, private snifferService: SnifferService) {
    this.snifferService.hostInfo.subscribe((hostInfo : HostInfo) => {
      this.hostInfo = hostInfo;
    });

    this.snifferService.hostInfo.subscribe((authInfo : AuthenticationInfo) => {
      if (authInfo.authenticated) {
        this.router.navigate(['capture']);
      } else {
        this.authenticationInfo = authInfo;
      }
    });
  }

  private subscribeClicked(password: string) : void {
    this.snifferService.sendAuthenticate(password);
  }

}
