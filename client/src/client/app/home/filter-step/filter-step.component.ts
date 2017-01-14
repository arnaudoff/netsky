import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferConfigurationService } from './../../shared/sniffer-configuration/index';

declare var $: any;

/**
 * This class represents the lazy loaded FilterStepComponent.
 */
@Component({
  moduleId: module.id,
  selector: 'filter-step',
  templateUrl: 'filter-step.component.html',
  styleUrls: ['filter-step.component.css'],
})
export class FilterStepComponent {
  private filters: string;

  constructor(private router: Router,
     private snifferConfigurationService: SnifferConfigurationService) {}

  ngAfterViewInit() {
    $('#filters-step')
        .addClass('active')
        .removeClass('disabled');
  }

  handleStep() {
    this.snifferConfigurationService.addFilter(this.filters);

    $('#filters-step')
        .addClass('disabled')
        .removeClass('active');

    this.router.navigate(['new/sharing']);
  }

}
