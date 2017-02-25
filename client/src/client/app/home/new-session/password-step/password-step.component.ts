import { Component, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferService, AuthenticationInfo } from './../../../shared/sniffer/index';

declare var $: any;

@Component({
  moduleId: module.id,
  selector: 'password-step',
  templateUrl: 'password-step.component.html'
})
export class PasswordStepComponent implements AfterViewInit {

  public password: string;

  public authenticationInfo: AuthenticationInfo = null;

  constructor(private router: Router, private snifferService: SnifferService) {
    this.snifferService.authenticationInfo
      .subscribe((authInfo : AuthenticationInfo) => {
        if (authInfo.isAuthenticated) {
          $('#password-step')
              .addClass('disabled')
              .removeClass('active');

          this.router.navigate(['home/new/interface']);
        } else {
          this.authenticationInfo = authInfo;
        }
      });
  }

  ngAfterViewInit() {
    $('#password-step')
        .addClass('active')
        .removeClass('disabled');
  }

  public handleStep() {
    if (this.password) {
      this.snifferService.sendAuthenticate(this.password);
    }
  }

}
