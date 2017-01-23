import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from './../../../shared/shared.module';
import { SnifferService } from './../../../shared/sniffer/index';
import { InterfaceService } from './../../../shared/interface/index';

import { InterfaceStepComponent } from './interface-step.component';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [InterfaceStepComponent],
  exports: [InterfaceStepComponent],
  providers: [SnifferService, InterfaceService]
})
export class InterfaceStepModule { }
