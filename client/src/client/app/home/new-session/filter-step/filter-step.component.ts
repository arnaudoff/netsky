import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferService } from './../../../shared/sniffer/index';

declare var $: any;

@Component({
  moduleId: module.id,
  selector: 'filter-step',
  templateUrl: 'filter-step.component.html'
})
export class FilterStepComponent implements AfterViewInit {

  public filterExpression: string;

  constructor(private router: Router, private snifferService: SnifferService) {}

  ngAfterViewInit() {
    $('#filters-step')
        .addClass('active')
        .removeClass('disabled');
  }

  handleStep() {
    this.snifferService.filterExpression = this.filterExpression;

    $('#filters-step')
        .addClass('disabled')
        .removeClass('active');

    this.router.navigate(['home/new/start']);
  }

}
