import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';
import { SnifferConfigBuilderService } from './../../shared/sniffer-config-builder/index';
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
     private snifferConfigBuilderService: SnifferConfigBuilderService,
     private snifferClientService: SnifferClientService)
  {}

  ngAfterViewInit() {
    $('#start-step')
        .addClass('active')
        .removeClass('disabled');
  }

  handleStep() {
    this.snifferClientService.startSniffer(
        this.snifferConfigBuilderService.interfaces,
        this.snifferConfigBuilderService.filters,
        this.snifferConfigBuilderService.listeners);

    this.router.navigate(['capture']);
  }

}
