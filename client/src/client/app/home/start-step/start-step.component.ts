import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferConfigurationService }
from './../../shared/sniffer-configuration/index';
import { SnifferClientService } from './../../shared/sniffer-client/index';

declare var $: any;

/**
 * This class represents the lazy loaded StartStepComponent.
 */
@Component({
  moduleId: module.id,
  selector: 'start-step',
  templateUrl: 'start-step.component.html',
  styleUrls: ['start-step.component.css'],
})

export class StartStepComponent {
  constructor(private router: Router,
     private snifferConfigurationService: SnifferConfigurationService,
     private snifferClientService: SnifferClientService)
  {}

  ngAfterViewInit() {
    $('#start-step')
        .addClass('active')
        .removeClass('disabled');
  }

  handleStep() {
    this.snifferClientService.startSniffer(
        this.snifferConfigurationService.interfaces,
        this.snifferConfigurationService.filters,
        this.snifferConfigurationService.listeners);

    this.router.navigate(['capture']);
  }

}
