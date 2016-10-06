import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';

//declare var $: JQueryStatic;

import { SnifferConfigBuilderService } from './../../shared/sniffer-config-builder/index';

/**
 * This class represents the lazy loaded InterfaceStepComponent.
 */
@Component({
  moduleId: module.id,
  selector: 'interface-step',
  templateUrl: 'interface-step.component.html',
  styleUrls: ['interface-step.component.css'],
})

export class InterfaceStepComponent {
  @ViewChild('selectInterfaces') selectElement: ElementRef;
  private interfaces: Array<string>;

  constructor(private router: Router,
     private snifferConfigBuilderService: SnifferConfigBuilderService) {}

  ngAfterViewInit() {
    // receive the available interfaces
    this.interfaces = ["eth0", "wlan0"];

    // initialize the dropdown with the received interfaces
    $(this.selectElement.nativeElement).dropdown();
  }

  handleStep() {
    // get value from the dropdown
    console.log($(this.selectElement.nativeElement).dropdown('get value'));

    // save to the config service
    this.snifferConfigBuilderService.add('interface', { "options": ['eth0'] });

    // navigate to the next route
    this.router.navigate(['./filter']);
  }

}
