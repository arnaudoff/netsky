import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferConfigBuilderService }
from './../../shared/sniffer-config-builder/index';

import { IConfigurableEntity }
from './../../shared/sniffer-config-builder/configurable-entity.interface';

declare var $: any;

/**
 * This class represents the lazy loaded SharingStepComponent.
 */
@Component({
  moduleId: module.id,
  selector: 'sharing-step',
  templateUrl: 'sharing-step.component.html',
  styleUrls: ['sharing-step.component.css'],
})

export class SharingStepComponent {
  @ViewChild('selectListeners') selectElement: ElementRef;
  private listeners: Array<Object>;

  constructor(private router: Router,
     private snifferConfigBuilderService: SnifferConfigBuilderService) {}

  ngAfterViewInit() {
    $('#sharing-step')
        .addClass('active')
        .removeClass('disabled');

    this.listeners = [
        { name: 'Ivaylo', addr: '192.168.1.12' },
        { name: 'July', addr: '192.168.1.13' }
    ];

    $(this.selectElement.nativeElement).dropdown({forceSelection: false});
  }

  handleStep() {
    let selectedElements: string =
        $(this.selectElement.nativeElement).dropdown('get value');
    let selectedListeners: Array<string> = selectedElements.split(',');

    let configurableEntity: IConfigurableEntity = { values: selectedListeners };

    this.snifferConfigBuilderService.listeners = configurableEntity;

    $('#sharing-step')
        .addClass('disabled')
        .removeClass('active');

    this.router.navigate(['new/start']);
  }

}
