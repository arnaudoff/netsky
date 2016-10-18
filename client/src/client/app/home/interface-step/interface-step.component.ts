import { Component, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { Router } from '@angular/router';
import { SnifferConfigBuilderService } from './../../shared/sniffer-config-builder/index';
import { SnifferClientService } from './../../shared/sniffer-client/index';

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

  constructor(
      private router: Router,
      private snifferConfigBuilderService: SnifferConfigBuilderService,
      private snifferClientService: SnifferClientService) {
    // TODO: send interface retrieval request here
  }

  ngAfterViewInit() {
    $('#interface-step')
        .addClass('active')
        .removeClass('disabled');

    this.snifferClientService.interfaces.subscribe(ifresponse => {
      ifresponse.names.forEach(ifname => this.interfaces.push({ name: ifname }));
    });

    $(this.selectElement.nativeElement).dropdown();
  }

  handleStep() {
    let selectedInterfaces: Array<string> =
        $(this.selectElement.nativeElement).dropdown('get value'));

    this.snifferConfigBuilderService.set_interfaces({ values: selectedInterfaces });

    $('#interface-step')
        .addClass('disabled')
        .removeClass('active');

    this.router.navigate(['home/filter']);
  }

}
