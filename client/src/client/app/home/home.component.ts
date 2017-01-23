import { Component } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferService, HostInfo } from './../shared/sniffer/index';

@Component({
  moduleId: module.id,
  selector: 'home',
  templateUrl: 'home.component.html'
})
export class HomeComponent {

  private hostInfo: HostInfo;

  constructor(private router: Router, private snifferService: SnifferService) {
    this.snifferService.sendHostCheck();

    this.snifferService.hostInfo.subscribe((hostInfo : HostInfo) => {
      this.hostInfo = hostInfo;
    });
  }

}
