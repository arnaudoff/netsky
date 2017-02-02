import { Component, ViewChild, ElementRef, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { SnifferService } from './../../../shared/sniffer/index';
import { InterfaceService, Interface } from './../../../shared/interface/index';

declare var $: any;

@Component({
  moduleId: module.id,
  selector: 'interface-step',
  templateUrl: 'interface-step.component.html'
})

export class InterfaceStepComponent implements OnInit {

  @ViewChild('interfaceName') selectElement: ElementRef;
  public interfaces: Array<Interface> = [];

  constructor(private router: Router,
              private snifferService: SnifferService,
              private interfaceService: InterfaceService) {}

  ngOnInit() {
    this.snifferService.retrieveInterfaces();

    $('#interface-step')
        .addClass('active')
        .removeClass('disabled');

    this.interfaceService.interfaces.subscribe((interfaces: Array<Interface>) => {
      interfaces.forEach((i: Interface) => this.interfaces.push(i));
    });

    $(this.selectElement.nativeElement).dropdown({forceSelection: false});
  }

  private handleStep() {
    let selectedInterface: string =
        $(this.selectElement.nativeElement).find(':selected').val();

    this.snifferService.interfaceName = selectedInterface;

    $('#interface-step')
        .addClass('disabled')
        .removeClass('active');

    this.router.navigate(['home/new/filter']);
  }

}
