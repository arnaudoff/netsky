import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { SharedModule } from './../../shared/shared.module';
import { InterfaceStepComponent } from './interface-step.component';
//import { SnifferClientService } from '../shared/sniffer-client/index';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [InterfaceStepComponent],
  exports: [InterfaceStepComponent]
//  providers: [SnifferClientService]
})

export class InterfaceStepModule { }
