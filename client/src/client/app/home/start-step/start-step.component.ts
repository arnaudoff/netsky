import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';
import { SnifferConfigBuilderService } from './../../shared/sniffer-config-builder/index';

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
     private snifferConfigBuilderService: SnifferConfigBuilderService) {}

  ngAfterViewInit() {
    $('#start-step')
        .addClass('active')
        .removeClass('disabled');
  }

  handleStep() {
    this.router.navigate(['capture']);
  }

}
