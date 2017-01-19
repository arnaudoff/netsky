import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferService } from './../../shared/sniffer/index';

declare var $: any;

@Component({
  moduleId: module.id,
  selector: 'filter-step',
  templateUrl: 'filter-step.component.html',
  styleUrls: ['filter-step.component.css'],
})
export class FilterStepComponent {

  private filters: string;

  constructor(private router: Router,
     private snifferService: SnifferService) {}

  ngAfterViewInit() {
    $('#filters-step')
        .addClass('active')
        .removeClass('disabled');
  }

  handleStep() {
    this.snifferService.addFilter(this.filters);

    $('#filters-step')
        .addClass('disabled')
        .removeClass('active');

    this.router.navigate(['new/start']);
  }

}
