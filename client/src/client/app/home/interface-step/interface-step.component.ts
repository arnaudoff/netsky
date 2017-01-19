import { Component, ViewChild, ElementRef, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferService } from './../../shared/sniffer/index';
import { InterfaceService, Interface } from './../../shared/interface/index';

declare var $: any;

@Component({
  moduleId: module.id,
  selector: 'interface-step',
  templateUrl: 'interface-step.component.html',
  styleUrls: ['interface-step.component.css'],
})

export class InterfaceStepComponent {

  @ViewChild('selectInterfaces') selectElement: ElementRef;
  private interfaces: Array<Interface> = [];

  constructor(private router: Router,
              private snifferService: SnifferService,
              private interfaceService: InterfaceService) {
  }

  ngOnInit() {
    this.snifferService.retrieveInterfaces();

    $('#interface-step')
        .addClass('active')
        .removeClass('disabled');

    this.interfaceService.interfaces.subscribe((interfaces: Array<Interface>) => {
      for (let entry of interfaces) {
          this.interfaces.push(entry);
      }
    });

    $(this.selectElement.nativeElement).dropdown({forceSelection: false});
  }

  private handleStep() {
    let selectedElements: Array<string> =
        $(this.selectElement.nativeElement).dropdown('get values');

    let selectedInterfaces: Array<string> = [];
    selectedElements.forEach((item, index) => {
        if (index < selectedElements.length - 1) {
            selectedInterfaces.push(item);
        }
    });

    selectedInterfaces
      .forEach(i => this.snifferService.addInterface(i));

    $('#interface-step')
        .addClass('disabled')
        .removeClass('active');

    this.router.navigate(['new/filter']);
  }

}
