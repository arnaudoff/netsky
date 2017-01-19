import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferService } from './../../shared/sniffer/index';

declare var $: any;

@Component({
  moduleId: module.id,
  selector: 'start-step',
  templateUrl: 'start-step.component.html',
  styleUrls: ['start-step.component.css'],
})

export class StartStepComponent {

  constructor(private router: Router, private snifferService: SnifferService) {}

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
