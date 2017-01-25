import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferService } from './../../../shared/sniffer/index';

declare var $: any;

@Component({
  moduleId: module.id,
  selector: 'start-step',
  templateUrl: 'start-step.component.html',
  styleUrls: ['start-step.component.css'],
})

export class StartStepComponent implements AfterViewInit {

  public interfaces: Array<string>;
  public filters: Array<string>;

  constructor(private router: Router, private snifferService: SnifferService) {
    this.interfaces = this.snifferService.interfaces;
    this.filters = this.snifferService.filters;
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
