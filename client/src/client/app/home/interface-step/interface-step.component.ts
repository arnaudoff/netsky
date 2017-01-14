import { Component, ViewChild, ElementRef, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferClientService, Interface, RetrievedInterfaces }
from './../../shared/sniffer-client/index';

import { SnifferConfigurationService } from './../../shared/sniffer-configuration/index';

declare var $: any;

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
  private interfaces: Array<Interface> = [];

  constructor(
      private router: Router,
      private snifferConfigurationService: SnifferConfigurationService,
      private snifferClientService: SnifferClientService) {
  }

  ngOnInit() {
    this.snifferClientService.retrieveInterfaces();

    $('#interface-step')
        .addClass('active')
        .removeClass('disabled');

    this.snifferClientService.interfaces.subscribe((retInterfaces: RetrievedInterfaces) => {
      for (let entry of retInterfaces.interfaces) {
          this.interfaces.push(entry);
      }
    });

    $(this.selectElement.nativeElement).dropdown({forceSelection: false});
  }

  handleStep() {
    let selectedElements: Array<string> =
        $(this.selectElement.nativeElement).dropdown('get values');

    let selectedInterfaces: Array<string> = [];
    selectedElements.forEach((item, index) => {
        if (index < selectedElements.length - 1) {
            selectedInterfaces.push(item);
        }
    });

    selectedInterfaces
      .forEach(i => this.snifferConfigurationService.addInterface(i));

    $('#interface-step')
        .addClass('disabled')
        .removeClass('active');

    this.router.navigate(['new/filter']);
  }

}
