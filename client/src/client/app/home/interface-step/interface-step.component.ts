import { Component, ViewChild, ElementRef, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferClientService } from './../../shared/sniffer-client/index';
import { IInterfaceResponseModel } from './../../shared/sniffer-client/index';

import { IRetrieveInterfacesResponseModel }
from './../../shared/sniffer-client/index';

import { IConfigurableEntity }
from './../../shared/sniffer-config-builder/configurable-entity.interface';

import { SnifferConfigBuilderService }
from './../../shared/sniffer-config-builder/index';

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
  private interfaces: Array<IInterfaceResponseModel> = [];

  constructor(
      private router: Router,
      private snifferConfigBuilderService: SnifferConfigBuilderService,
      private snifferClientService: SnifferClientService) {
  }

  ngOnInit() {
    this.snifferClientService.retrieveInterfaces();

    $('#interface-step')
        .addClass('active')
        .removeClass('disabled');

    this.snifferClientService.interfaces.subscribe((ifresponse: IRetrieveInterfacesResponseModel) => {
      for (let entry of ifresponse.interfaces) {
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

    let configurableEntity: IConfigurableEntity = { values: selectedInterfaces };
    this.snifferConfigBuilderService.interfaces = configurableEntity;

    $('#interface-step')
        .addClass('disabled')
        .removeClass('active');

    this.router.navigate(['home/filter']);
  }

}
