import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from './../../shared/shared.module';
import { InterfaceStepComponent } from './interface-step.component';
import { SnifferConfigurationService } from './../../shared/sniffer-configuration/index';
import { SnifferClientService } from './../../shared/sniffer-client/index';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [InterfaceStepComponent],
  exports: [InterfaceStepComponent],
  providers: [SnifferConfigurationService, SnifferClientService]
})
export class InterfaceStepModule { }
