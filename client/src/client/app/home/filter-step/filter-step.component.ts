import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';
import { SnifferConfigBuilderService } from './../../shared/sniffer-config-builder/index';

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
     private snifferConfigBuilderService: SnifferConfigBuilderService) {}

  ngAfterViewInit() {
    $('#filters-step')
        .addClass('active')
        .removeClass('disabled');
  }

  handleStep() {
    this.snifferConfigBuilderService.filters = { values: [this.filters] };

    $('#filters-step')
        .addClass('disabled')
        .removeClass('active');

    this.router.navigate(['home/sharing']);
  }

}
