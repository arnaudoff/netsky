import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferService } from './../../../shared/sniffer/index';

declare var $: any;

@Component({
  moduleId: module.id,
  selector: 'start-step',
  templateUrl: 'start-step.component.html'
})

export class StartStepComponent implements AfterViewInit {

  public interfaceName: string;
  public filterExpression: string;

  constructor(private router: Router, private snifferService: SnifferService) {
    this.interfaceName = this.snifferService.interfaceName;
    this.filterExpression = this.snifferService.filterExpression;
  }

  ngAfterViewInit() {
    $('#start-step')
        .addClass('active')
        .removeClass('disabled');
  }

  handleStep() {
    this.snifferService.start();
    this.router.navigate(['capture']);
  }

}
